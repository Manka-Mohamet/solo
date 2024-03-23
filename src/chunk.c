#include "../include/chunk.h"
#include "../include/memory.h"


void initChunk(Chunk* chunk){
	chunk->length = 0;
	chunk->capacity = 0;
	chunk->bytecode = NULL;
	chunk->lines = NULL;
	initValueArray(&chunk->constants);
}



void writeChunk(Chunk* chunk, uint8_t byte, int line){
	if (chunk->length + 1 > chunk->capacity){
		int capacity = GROW_CAPACITY(chunk->capacity);
		chunk->bytecode = GROW_ARRAY(uint8_t, chunk->bytecode, chunk->capacity, capacity);
		chunk->lines    = GROW_ARRAY(int, chunk->lines, chunk->capacity, capacity);
	}

	chunk->bytecode[chunk->length] = byte;
	chunk->lines[chunk->length] = line;
	chunk->length++;

}


int addConstant(Chunk* chunk, Value value){
	writeValueArray(&chunk->constants, value);
	return chunk->constants.length - 1;
}




void freeChunk(Chunk* chunk){
	FREE_ARRAY(uint8_t, chunk->bytecode, chunk->capacity);
	FREE_ARRAY(int, chunk->lines, chunk->capacity);
	freeValueArray(&chunk->constants);
	initChunk(chunk);

}





