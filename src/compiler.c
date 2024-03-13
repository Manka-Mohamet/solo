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
