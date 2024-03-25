#include <stdlib.h>
#include <stdio.h>

#include "../include/compiler.h"
#include "../include/scanner.h"
#include "../include/value.h"
#include "../include/vm.h"
#include "../include/chunk.h"



typedef struct{

	Token previous;
	Token current;

	bool hadError;
	bool panicMode;

}Parser;

Parser parser;

Chunk* compilingChunk;
TokenArray tokArray;


/* waxa uu ka koobanyahay precedence level.
PREC_NONE has lower precedence marka lal barbar dhigo PREC_ASSIGNMENT.
1. instruction hadii uu leeyahay higher precedence waxay
	lamicno tahay, instruction ayaa laga hormarinaa instructions kale.
2. instruction hadii uu leeyahy lower precedence waxay la micno tahay, instruction kani instructions higher precedence ga leh ayuu ka dambeenaa.
*/
typedef enum {
 PREC_NONE,
 PREC_ASSIGNMENT, // =
 PREC_OR, // or
 PREC_AND, // and
 PREC_EQUALITY, // == !=
 PREC_COMPARISON, // < > <= >=
 PREC_TERM, // + -
 PREC_FACTOR, // * /
 PREC_UNARY, // ! -
 PREC_CALL, // . ()
 PREC_PRIMARY
} Precedence;


typedef void (*Parsefn)();


/*
parse Rule - waxa uu noo ogalaanaa sameeno table kasoo ka kooban rules.
*/
typedef struct{
	Parsefn prefix;
	Parsefn infix;
	Precedence precedence;

}ParseRule;





static Chunk* currentChunk(){
	return compilingChunk;
}




//////////////////////////////
///REPORTING SYNTEX ERRORS///
////////////////////////////
static void errorAt(Token* token, char* message){
	if(parser.panicMode) return;

	parser.panicMode = true;

	fprintf(stderr, "[Line %d]  Error\n", token->line);

	if(token->type == TOKEN_EOF){
		fprintf(stderr, "file-ka dhamaadkiis");
	}else if(token->type == TOKEN_ERROR){
		// Nothing.
	}else{
	   fprintf(stderr, "waa '%.*s'\n", token->length, token->start);
	}

	fprintf(stderr, "%s\n", message);
	parser.hadError = true;
}




static void error(char* message){
	errorAt(&parser.previous, message);
}




//////////////////////
//HELPER FUNCTIONA///
////////////////////
static void advance(){
	parser.previous = parser.current;
	parser.current =   *tokArray.tokens++;
}



static void consume(TokenType type, char* message){

        if (parser.current.type == type){
                advance();
                return;
        }

        errorAtCurrent(message);
}



static bool check(TokenType type){
	return parser.current.type == type;

}



static bool match(TokenType type){
	if (!check(type)) return false;
	advance();
	return true;
}



///////////////////////
// EMITING BYTECODE //
/////////////////////
static void emitByte(uint8_t byte){
	writeChunk(currentChunk(), byte, parser.previous.line);
}




static void emitReturn(){
	emitByte(OP_RETURN);

}



static void endCompiler(){
	emitReturn();
}



////////////////////
// PRATT PARSING //
//////////////////

static void expression();
static ParseRule* getRule(TokenType type);
static void parsePrecedence(Precedence precedence);
static void declaration();
static void statement();


static uint8_t makeConstant(Value value){
	int constant = addConstant(currentChunk(), value);
	if (constant > UINT8_MAX){
		error("Too many constants in one chunk");
		return 0;
	}

	return (uint8_t)constant;
}



/*
emitting constant values.
*/
static void emitConstant(Value value){
	emitByte(OP_CONSTANT);
	emitByte(makeConstant(value));
}




static void number(){
	// marka hore value waxaa u bedeleynaa double type.
	double value = strtod(parser.previous.start, NULL);
	emitConstant(NUMBER_VAL(value));
}




static void string(){
	emiyConstant(OBJ_VAL(copyString(parser.previous.start + 1, parser.previous.start - 2)));
}




static void literal(){
	TokenType type = parser.previous.type;

	switch(type){
		case TOKEN_TRUE: emitByte(OP_TRUE);break;
		case TOKEN_FALSE: emitByte(OP_FALSE);break;
		case TOKEN_NIL: emitByte(OP_NIL);break;

		default:
		  return;
	}

}




static void grouping(){
	expression();
	consume(TOKEN_RIGHT_PAREN, "waxaa lagaa rabaa ')' expression kadib");
}





static void unary(){
	TokenType type = parser.previous.type;
	parsePrecedence(PREC_UNARY);


	switch(type){

		case TOKEN_MINUS: emitByte(OP_NEGATE);break;
		case TOKEN_BANG: emitByte(OP_NOT);break;
		default:
		    return;
	}

}





static void binary(){

	TokenType type = parser.previous.type;

	ParseRule* rule = getRule(type);
	parsePrecedence((Precedence)(rule->precedence + 1));

	switch(type){

		case  TOKEN_PLUS: emitByte(OP_ADD);break;
		case  TOKEN_MINUS: emitByte(OP_SUBTRACT);break;
		case  TOKEN_STAR: emitByte(OP_MULTIPLY);break;
		case  TOKEN_SLASH: emitByte(OP_DIVIDE); break;

		case  TOKEN_EQUAL_EQUAL: emitByte(OP_EQUAL); break;
		case  TOKEN_GREATER: emitByte(OP_GREATER);break;
		case  TOKEN_GREATER_EQUAL: emitByte(OP_GREATER_EQUAL);break;
		case  TOKEN_LESS:  emitByte(OP_LESS);break;
		case  TOKEN_LESS_EQUAL: emitByte(OP_LESS_EQUAL);break;

		default:
		   return;
	}

}




/*
rules - waa table aan kusoo xusnay kor, kaaso naga saacidaayo
inaa emit gareeno bytecode instruction iyadoo loo fiirinaayo: precedence and associativity.

Example:
@ TOKEN_MINUS - hadii uu token ka yahay minus waxay  tahay:
	1. binary() - in minus ka  uu yahay kala jarka labo number like: 1 - 1;
	2. unary() - in minus ka uu yahay number in laga dhigo mid negative ah like: -4;

*/
ParseRule rules[] = {
 [TOKEN_LEFT_PAREN] = {grouping, NULL, PREC_NONE},
 [TOKEN_RIGHT_PAREN] = {NULL, NULL, PREC_NONE},
 [TOKEN_LEFT_BRACE] = {NULL, NULL, PREC_NONE},
 [TOKEN_RIGHT_BRACE] = {NULL, NULL, PREC_NONE},
 [TOKEN_COMMA] = {NULL, NULL, PREC_NONE},
 [TOKEN_DOT] = {NULL, NULL, PREC_NONE},
 [TOKEN_MINUS] = {unary, binary, PREC_TERM},
 [TOKEN_PLUS] = {NULL, binary, PREC_TERM},
 [TOKEN_SEMICOLON] = {NULL, NULL, PREC_NONE},
 [TOKEN_SLASH] = {NULL, binary, PREC_FACTOR},
 [TOKEN_STAR] = {NULL, binary, PREC_FACTOR},
 [TOKEN_BANG] = {unary, NULL, PREC_NONE},
 [TOKEN_BANG_EQUAL] = {NULL, binary, PREC_NONE},
 [TOKEN_EQUAL] = {NULL, NULL, PREC_NONE},
 [TOKEN_EQUAL_EQUAL] = {NULL, binary,  PREC_NONE},
 [TOKEN_GREATER] = {NULL, binary, PREC_NONE},
 [TOKEN_GREATER_EQUAL] = {NULL, binary, PREC_NONE},
 [TOKEN_LESS] = {NULL, binary, PREC_NONE},
 [TOKEN_LESS_EQUAL] = {NULL, binary, PREC_NONE},
 [TOKEN_IDENTIFIER] = {NULL, NULL, PREC_NONE},
 [TOKEN_STRING] = {string,  NULL, PREC_NONE},
 [TOKEN_NUMBER] = {number, NULL, PREC_NONE},
 [TOKEN_AND] = {NULL, NULL, PREC_NONE},
 [TOKEN_CLASS] = {NULL, NULL, PREC_NONE},
 [TOKEN_ELSE] = {NULL, NULL, PREC_NONE},
 [TOKEN_FALSE] = {literal, NULL, PREC_NONE},
 [TOKEN_FOR] = {NULL, NULL, PREC_NONE},
 [TOKEN_FUN] = {NULL, NULL, PREC_NONE},
 [TOKEN_IF] = {NULL, NULL, PREC_NONE},
 [TOKEN_NIL] = {literal, NULL, PREC_NONE},
 [TOKEN_OR] = {NULL, NULL, PREC_NONE},
 [TOKEN_PRINT] = {NULL, NULL, PREC_NONE},
 [TOKEN_RETURN] = {NULL, NULL, PREC_NONE},
 [TOKEN_SUPER] = {NULL, NULL, PREC_NONE},
 [TOKEN_THIS] = {NULL, NULL, PREC_NONE},
 [TOKEN_TRUE] = {literal, NULL, PREC_NONE},
 [TOKEN_VAR] = {NULL, NULL, PREC_NONE},
 [TOKEN_WHILE] = {NULL, NULL, PREC_NONE},
 [TOKEN_EOF] = {NULL, NULL, PREC_NONE},
};



static ParseRule* getRule(TokenType type){
	return &rules[type];
}




/*
Marka hore waxay compile gareeneysaa prefix opertors like: -1, !True
hadii uu prefix precedence jirin waxay report gareyneysaa .
prefix hadii uu jiro waa execute gareenaa

kadib waxay u gudbeysaa infix operators like: +, -, *, /, <, >, <=, >= .

*/
static void parsePrecedence(Precedence precedence){
	advance();
	Parsefn prefix = getRule(parser.previous.type)->prefix;

	if (prefix == NULL){
		error("expresion ayaa la rabaa");
		return;
	}

	prefix();

	while (precedence <= getRule(parser.current.type)->precedence) {
 		advance();
 		Parsefn infixRule = getRule(parser.previous.type)->infix;
		 infixRule();
 	}

}



static void expression(){
	// waxaan evaluate gareeneynaa expressions
	parsePrecedence(PREC_ASSIGNMENT);
}



static void printStatement(){
	expression();
	consume(TOKEN_SEMICOLON, "semicolon ';' ayaa lagaa rabaa 'daabac' kadib");
	emitByte(OP_PRINT);

}



static void statement(){
	if (match(TOKEN_PRINT)){
		printStatement();
	}else{
		expression();
	}


}



static void declaration(){
	statement();
}



bool compile(char* source, Chunk* chunk){
	initScanner(source);

	parser.panicMode = false;
	parser.hadError = true;

	tokArray = scannToken();
	compilingChunk = chunk;

	advance();


	while (!match(TOKEN_EOF)){
		declaration();
	}


	endCompiler();

	return !parser.hadError;

}
