#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "../include/value.h"
#include "../include/vm.h"
#include "../include/memory.h"
#include "../include/chunk.h"
#include "../include/compiler.h"


VM vm;

static void resetStack(){
	freeStack(&vm);
}



void initVM(){
	vm.stackTop = vm.stack;
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

/*
static bool stackEmpty(){
	return vm.length <= 0;
}
*/

static Value peek(int distance){
	return vm.stackTop[-1 - distance];
}

static bool valuesEqual(Value a,  Value b){
	if (a.type !=  b.type) return false;

	switch(a.type){
		case BOOL: return AS_BOOL(a) == AS_BOOL(b); break;
		case NIL:  return true;
		case NUMBER: return AS_NUMBER(a) == AS_NUMBER(b); break;
		default:
		  return false;
	}

}


static bool  isFalsey(Value value){
	return IS_NIL(value) || (IS_BOOL(value) && !AS_BOOL(value));
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


static void runtimeError(const char* format, ...){
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	fputs("\n", stderr);

	size_t instruction = vm.ip - vm.chunk->bytecode - 1;
	int line = vm.chunk->lines[instruction];

	fprintf(stderr, "[line %d ]\n", line);
	resetStack();
}


/*
run() - waa wadnaha program ka,  90% shaqada luuqada waxaa qabanaayo function kan
waxaan isticmaalnay big switch case si aan u execte gareeno instruction waliba.
*/
InterpretResult run(){

	#define READ_BYTE()  (*vm.ip++)
	#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])


	#define BINARY_OP(valueType, op) \
 	do { \
 		if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) { \
		 runtimeError("Operands waa inay ahaadaan numbers."); \
 		 return INTERPRET_RUNTIME_ERROR; \
 		} \
 		double b = AS_NUMBER(pop()); \
 		double a = AS_NUMBER(pop()); \
 		push(valueType(a op b)); \
 	} while (false)




	for(;;){

	   uint8_t  instruction;
	   switch(instruction = READ_BYTE()){

		case OP_CONSTANT:{
			Value constant = READ_CONSTANT();
			push(constant);
			break;
		}

		// statements not declarations.
		case OP_PRINT:{
			printValue(pop());
			printf("\n");
			break;
		}



		// unary operators.
		case OP_NEGATE: {
       		   if (IS_NUMBER(peek(0))){
			runtimeError("operand lasiinaayo negative waa inuu yahay number");
			return INTERPRET_RUNTIME_ERROR;
		   }

		   push(NUMBER_VAL(-AS_NUMBER(pop())));
		   break;

		}

		case OP_NOT:  push(BOOL_VAL(isFalsey(pop()))); break;



		// four binary arithmatic operations
		case OP_ADD: BINARY_OP(NUMBER_VAL, +); break;
		case OP_SUBTRACT: BINARY_OP(NUMBER_VAL, -); break;
		case OP_MULTIPLY: BINARY_OP(NUMBER_VAL, *);break;
		case OP_DIVIDE: BINARY_OP(NUMBER_VAL, /); break;



		// four types of comparison operations.
		case OP_GREATER: BINARY_OP(BOOL_VAL,  >); break;
		case OP_LESS:   BINARY_OP(BOOL_VAL, <); break;
		case OP_GREATER_EQUAL: BINARY_OP(BOOL_VAL, >=);
		case OP_LESS_EQUAL: BINARY_OP(BOOL_VAL, <=);break;
		case OP_EQUAL: {
			Value b = pop();
			Value a = pop();
			push(BOOL_VAL(valuesEqual(a, b))); break;
		}



		// literals
		case OP_NIL: push(NIL_VAL);break;
		case OP_TRUE: push(BOOL_VAL(true));break;
		case OP_FALSE: push(BOOL_VAL(false));break;


		case OP_RETURN:
			return INTERPRET_OK;

	}

	}


	#undef READ_BYTE
	#undef READ_CONSTANT
	#undef BINARY_OP
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
