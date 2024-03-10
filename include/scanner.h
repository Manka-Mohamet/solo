#ifndef sola_scanner_h
#define sola_scanner_h






typedef enum{
	//single charecters
	TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
	TOKEN_LEFT_BRACE, TOKEN_RIGTH_BRACE,
	TOKEN_PLUS, TOKEN_MINUS, TOKEN_STAR,
	TOKEN_SLASH, TOKEN_DOT, TOKEN_SEMICOLON,
	TOKEN_COMMA,


	// more than 1 or 2 charecters
	TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
	TOKEN_LESS_EQUAL, GREATER_EQUAL,
	TOKEN_BANG, TOKEN_BANG_EQUAL,

	 //literals
	TOKEN_STRING, TOKEN_IDENTIFIER, TOKEN_NUMBER,


	// keywords
	TOKEN_AND, TOKEN_OR, TOKEN_IF,
	TOKEN_ELSE, TOKEN_FOR, TOKEN_WHILE,
	TOKEN_CLASS, TOKEN_FUNC, TOKEN_RETURN,
	TOKEN_RPINT, TOKEN_THIS, TOKEN_VAR,
	TOKEN_SUPET, TOKEN_TRUE, TOKEN_FALSE,
	TOKEN_NIL,   TOKEN_EXTEND,

	// end and error charecters
	TOKEN_ERROR, TOKEN_EOF,

}TokenType;




typedef struct{
	TokenType type;
	char* start
	int length;
	int line;

}Token;



typedef struct{

	int count;
	int capacity;
	Token* tokens;

}TokenArray;

void writeToken(TokenArray* array, Token token);

void freeToken(TokenArray* array);


void initScanner(const char* source);

#endif
