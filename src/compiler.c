#include <stdlib.h>
#include <stdio.h>

#include "../include/compiler.h"
#include "../include/scanner.h"


typedef struct{

	Token previous;
	Token current;

	bool hadError;
	bool panicMode;

}Parser;

Parser parser;

Chunk* compilingChunk;


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
	parsefn prefix;
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

	printf("\033[0;31m");
	fprintf(stderr, "[Line %d] Error", token->line);

	if(token->type == TOKEN_EOF){
		fprintf(stderr, "dhamaadka file-ka");
	}else if(token->type == TOKEN_ERROR){
		// Nothing.
	}else{
	   fprintf(stderr, "waa  '%.*s'", token->length, token->start);
	}

}




static void errorAtCurrent(char* message){
	errorAt(&parser.current, message);
}





static void error(char* message){
	errorAt(&parser.previous, message);
}




//////////////////////
//HELPER FUNCTIONA///
////////////////////
Token* tokenIndex = NULL;

static void advance(){
	parser.previous = parser.current;

	for(;;){

	   parser.current =  *tokenIndex++;

	   if (parser.current.type != TOKEN_ERROR) break;

	   errorAtCurrent(parser.current.start);

	}

}



static void consume(TokenType type, char* message){

        if (parser.current.type == type){
                advance();
                return;
        }

        errorAtCurrent(message);
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


static uint8_t makeConstant(double value){
	int constant = addConstant(currentChunk(), value);
	if (constant > UINT8_MAX){
		error("Too many constants in one chunk");
		return;
	}

	return (uint8_t)constant;
}

/*
emitting constant values.
*/
static void emitConstant(double value){
	emitByte(OP_CONSTANT);
	emitByte(makeConstant(value));
}


static void number(){
	// marka hore value waxaa u bedeleynaa double type.
	double value = strtod(parser.previous.start, NULL);
	emitConstant(value);
}



static void grouping(){
	expression();
	consume(TOKEN_RIGHT_PAREN, "waxaa lagaa rabaa ')' expression kadib");
}




static void unary(){
	TokenType type = parser.previous.type;
	parsePrecedence(PREC_UNARY);


	switch(type){

		case TOKEN_MINUS: emitByte(OP_NEGATE);
		default:
		    return;
	}

}




static void binary(){

	TokenType type = parser.previous.type;

	ParseRule* rule = getRule(type);
	parsePrecedence((Precedence)(rule->precedence + 1));

	switch(type){

		case  TOKEN_PLUS: emitByte(OP_ADD);
		case  TOKEN_MINUS: emitByte(OP_SUBTRACT);
		case  TOKEN_STAR: emitByte(OP_MULTIPLY);
		case  TOKEN_SLASH: emitByte(OP_DIVIDE); 
		case  TOKEN_GREATER: emitByte(OP_GREATER);
		case  TOKEN_GREATER_EQUAL: emitByte(OP_GREATER_EQUAL);
		case  TOKEN_LESS:  emitByte(OP_LESS);
		case  TOKEN_LESS_GREATER: emitByte(OP_LESS_EQUAL);

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
 [TOKEN_BANG] = {NULL, NULL, PREC_NONE},
 [TOKEN_BANG_EQUAL] = {NULL, NULL, PREC_NONE},
 [TOKEN_EQUAL] = {NULL, NULL, PREC_NONE},
 [TOKEN_EQUAL_EQUAL] = {NULL, NULL, PREC_NONE},
 [TOKEN_GREATER] = {NULL, NULL, PREC_NONE},
 [TOKEN_GREATER_EQUAL] = {NULL, NULL, PREC_NONE},
 [TOKEN_LESS] = {NULL, NULL, PREC_NONE},
 [TOKEN_LESS_EQUAL] = {NULL, NULL, PREC_NONE},
 [TOKEN_IDENTIFIER] = {NULL, NULL, PREC_NONE},
 [TOKEN_STRING] = {NULL, NULL, PREC_NONE},
 [TOKEN_NUMBER] = {number, NULL, PREC_NONE},
 [TOKEN_AND] = {NULL, NULL, PREC_NONE},
 [TOKEN_CLASS] = {NULL, NULL, PREC_NONE},
 [TOKEN_ELSE] = {NULL, NULL, PREC_NONE},
 [TOKEN_FALSE] = {NULL, NULL, PREC_NONE},
 [TOKEN_FOR] = {NULL, NULL, PREC_NONE},
 [TOKEN_FUN] = {NULL, NULL, PREC_NONE},
 [TOKEN_IF] = {NULL, NULL, PREC_NONE},
 [TOKEN_NIL] = {NULL, NULL, PREC_NONE},
 [TOKEN_OR] = {NULL, NULL, PREC_NONE},
 [TOKEN_PRINT] = {NULL, NULL, PREC_NONE},
 [TOKEN_RETURN] = {NULL, NULL, PREC_NONE},
 [TOKEN_SUPER] = {NULL, NULL, PREC_NONE},
 [TOKEN_THIS] = {NULL, NULL, PREC_NONE},
 [TOKEN_TRUE] = {NULL, NULL, PREC_NONE},
 [TOKEN_VAR] = {NULL, NULL, PREC_NONE},
 [TOKEN_WHILE] = {NULL, NULL, PREC_NONE},
 [TOKEN_ERROR] = {NULL, NULL, PREC_NONE},
 [TOKEN_EOF] = {NULL, NULL, PREC_NONE},
};



static ParseRule* getRule(TokenType type){
	return &rule[type];
}




/*
Marka hore waxay compile gareeneysaa prefix opertors like: -1, !True
hadii uu prefix precedence jirin waxay report gareyneysaa .
prefix hadii uu jiro waa execute gareenaa

kadib waxay u gudbeysaa infix operators like: +, -, *, /, <, >, <=, >= .

*/
static void parsePrecedence(Precedence precedence){
	advance();
	ParseRule* prefix = getRule(parser.previous.type)->prefix;

	if (prefix == NULL){
		error("expresion ayaa la rabaa");
		return;
	}

	prefix();

	while (precedence <= getRule(parser.current.type)->precedence) {
 		advance();
 		ParseFn infixRule = getRule(parser.previous.type)->infix;
		 infixRule();
 	}

}



static void expression(){
	// waxaan evaluate gareeneynaa expressions
	parsePrecedence(PREC_ASSIGNMENT);
}




bool compile(char* source, Chunk* chunk){
	initScanner(source);

	parser.panicMode = false;
	parser.hadError = true;

	compilingChunk = chunk;

	tokenIndex = scannToken()->tokens;
	advance();
	//expresion();
	consume(TOKEN_EOF, "expression-ka inay dhamaato ayaa la filaa");

	endCompiler();

	return !parser.hadError;

}
