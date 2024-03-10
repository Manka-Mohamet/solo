#include <stdlib.h>
#include <stdio.h>

#include "../include/vm.h"
#include "../include/memory.h"
#include "../include/chunk.h"

VM vm;


void push(Value value){
	if (vm.capacity < vm.length + 1){
		int OldCapacity = vm.capacity;
		vm.capacity = GROW_CAPACITY(OldCapacity);
		vm.stack = GROW_ARRAY(Value, vm.stack, OldCapacity, vm.capacity);
	}

	vm.stackTop = value;
	vm.stackTop++;
	vm.length++;
}




Value pop(){

	if (vm.length < 0){
		return;
	}

	vm.length--;
	vm.stackTop--;
	return *vm.stackTop;

}


/*
run() - waa wadnaha program ka,  90% shaqada luuqada waxaa qabanaayo function kan
waxaan isticmaalnay big switch case si aan u execte gareeno instruction waliba.
*/
InterpretResult run(){

	#define READ_BYTE  (*vm.ip++)



	for(;;){

	   uint8_t instruction;
	   switch(instruction = READ_BYTE()){
		case OP_NEGATE:
			push(VAL_NUMBER(-pop()));
	  }

	}


	#undef READ_BYTE



}




InterpretResult interpret(const char* source){
	Chunk chunk;
	initChunk(&chunk);

	if (!compile(source, &chunk){
		freeChunk(&chunk);
		return INTERPRET_COMPILE_ERROR;
	}

	vm.chunk = &chunk;
	vm.stackTop = vm.stack;
	vm.ip = vm.chunk->bytecode;

	InterpretResult result = run();

	free(&chunk);
	free(&vm);

	return result;

}
