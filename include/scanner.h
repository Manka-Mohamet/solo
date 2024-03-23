#ifndef solo_scanner_h
#define solo_scanner_h

/*

Scanner - waa the first step in  compiler design and implementation.
waxaa loo adeegsadaa in charecter waliba laga dhigo token si uu compiler-ka hadhow parsing u sameeyo.

waa meesha lagu skip gareeyo:
	1. comments
	2. newlines
	3. tabs and whitespaces. 

*/



/*
TokenType - waxa uu ka koobanyahay every possible tokens 
ee aynu isticmaaleyno.

*/
typedef enum{
	//single charecters
	TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
	TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
	TOKEN_PLUS, TOKEN_MINUS, TOKEN_STAR,
	TOKEN_SLASH, TOKEN_DOT, TOKEN_SEMICOLON,
	TOKEN_COMMA,


	// more than 1 or 2 charecters
	TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
	TOKEN_LESS, TOKEN_LESS_EQUAL, 
	TOKEN_GREATER, TOKEN_GREATER_EQUAL,
	TOKEN_BANG, TOKEN_BANG_EQUAL,

	 //literals
	TOKEN_STRING, TOKEN_IDENTIFIER, TOKEN_NUMBER,


	// keywords
	TOKEN_AND, TOKEN_OR, TOKEN_IF,
	TOKEN_ELSE, TOKEN_FOR, TOKEN_WHILE,
	TOKEN_CLASS, TOKEN_FUN, TOKEN_RETURN,
	TOKEN_PRINT, TOKEN_THIS, TOKEN_VAR,
	TOKEN_SUPER, TOKEN_TRUE, TOKEN_FALSE,
	TOKEN_NIL,   TOKEN_EXTENDS,  TOKEN_INPUT,

	// end and error charecters
	TOKEN_ERROR, TOKEN_EOF,

}TokenType;



/*
Token - waa charecter waliba ee ku jira source code ka 
waxaa laga dhigaa Tokens.
Example - print "hello, world";
	Token{
	   type = TOKEN_PRINT,
	   start = pointer to the first charecter of print.
	   length = the length of print = 5
	   line = file ka line number kiisa ee  print "hello, world"; lagu qoray.
	}

*/
typedef struct{
	TokenType type;
	char* start;
	int length;
	int line;

}Token;



/*

TokenArray - dynamic array kasoo hold gareyneesa dhamaan  Token() in linear array,
si uu compiler-ka looping ugu sameeyo TokenArray.

*/
typedef struct{

	int count;
	int capacity;
	Token* tokens;

}TokenArray;

// writeToken - append new Token to the TokenArray.
void writeToken(TokenArray* array, Token token);

//freeToken - free garee dynamic array, markaan isticmaalno kadib.
void freeToken(TokenArray* array);

//initScanner - waxay initialize gareenee New Scanner.
void initScanner(char* source);


TokenArray scannToken();


#endif
