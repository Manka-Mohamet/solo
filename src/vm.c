#include <stdlib.h>
#include <stdio.h>

#include "../include/value.h"
#include "../include/vm.h"
#include "../include/memory.h"
#include "../include/chunk.h"
#include "../include/compiler.h"


VM vm;

static void resetStack(){
	vm.stackTop = vm.stack;
}

void initVM(){
	resetStack();

}



void push(Value value){
	if (vm.capacity < vm.length + 1){
		int OldCapacity = vm.capacity;
		vm.capacity = GROW_CAPACITY(OldCapacity);
		vm.stack = GROW_ARRAY(Value, vm.stack, OldCapacity, vm.capacity);
	}

	*vm.stackTop = value;
	vm.stackTop++;
	vm.length++;
}




Value pop(){

	if (vm.length < 0){
		fprintf(stderr, "There is no instruction to pop of from the stack.");
		exit(79);
	}

	vm.length--;
	vm.stackTop--;
	return *vm.stackTop;

}




void freeStack(VM* vm){
	FREE_ARRAY(Value, vm->stack, vm->capacity);
	vm->length = 0;
	vm->capacity = 0;
	vm->stack = NULL;
	vm->stackTop = NULL;
	vm->chunk = NULL;
	vm->ip = NULL;
}



/*
run() - waa wadnaha program ka,  90% shaqada luuqada waxaa qabanaayo function kan
waxaan isticmaalnay big switch case si aan u execte gareeno instruction waliba.
*/
InterpretResult run(){

	#define READ_BYTE()  (*vm.ip++)



	for(;;){

	   uint8_t  instruction;
	   switch(instruction = READ_BYTE()){
		case OP_RETURN:
			return INTERPRET_OK;


	}

	}


	#undef READ_BYTE



}




InterpretResult interpret(char* source){
	Chunk chunk;
	initChunk(&chunk);

	if (!compile(source, &chunk)){
		freeChunk(&chunk);
		return INTERPRET_COMPILE_ERROR;
	}

	vm.chunk = &chunk;
	vm.ip = vm.chunk->bytecode;

	InterpretResult result = run();

	freeChunk(&chunk);
	freeStack(&vm);

	return result;

}



void freeVM(){

}
