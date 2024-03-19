/*
file waa basic representation of our code.
waxaa jira different way eeloo represent gareeyo language waxaa kamid ah:
	1. Abstract Syntex Tree (ASTs)
	2. ByteCode (Custom Instruction Set)
	3. Machine Code (0s and 1s)
*/


#ifndef sola_chunk_h
#define sola_chunk_h

#include "common.h"
#include "value.h"



/*
 OpCode short for Operational code  waa instructions uu Virtual Machine ka execute gareenaayo.
 example:
	OP_ADD
	b = pop();
	a = pop();
	push(a + b)
explanation: it the virtual machine la kulmo OP_ADD, labada values ee ugu koreeso stack 
	ayuu isku daraa kadibna result ga soo baxa ayuu stack ku push gareenaa.
*/
typedef enum{

	OP_ADD,
	OP_SUBTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,

	OP_NEGATE,
	OP_NOT,

	OP_GREATER,
	OP_GREATER_EQUAL,
	OP_LESS,
	OP_LESS_EQUAL,
	OP_EQUAL,

	OP_FALSE,
	OP_TRUE,
	OP_NIL,

	OP_CONSTANT,

	OP_PRINT,
	OP_RETURN,


}OpCode;



/*
@Description - Chunk struct waa  "thick pointer"
user can't Chunk access directly instead they use interface functions provided below 
Chunk struct waa dynamic array, waxa uu isticmaalaa 

@length    -  waxa uu hold gareenaa total elements in the array.
@capacity  -  waxa uu hold gareenaa total capacity alocated for this array.
@bytecode  -  waa pointer to bytecode instructions
@lines     -  waa line numbers, waxaynu ubaahanaynaa markii aynu report gareeneeno RuntimeErro
@constants -  waa constant values : number, string etc.
*/
typedef struct {
	int length;
	int capacity;
	uint8_t* bytecode;
	int* lines;
	ValueArray constants;

}Chunk;

/*
initChunk() waxa uu initialize gareenaa new Chunk.
so that you write to this initialized chunk.
*/
void initChunk(Chunk* chunk);


/*
writeChunk() waxa uu keedinaa bytecode instructions iyo line number.
*/
void writeChunk(Chunk* chunk, uint8_t byte, int line);


/*
addConstant() waxay naga caawinaysaa inaan  keydino values directly inside the Chunk.
*/
int addConstant(Chunk* chunk, Value value);


/*
freeChunk() waxa uu free gareenaa Chunk memory aan allocate gareenay.
si aysan udhicin memory failure.
*/
void freeChunk(Chunk* chunk);


#endif
