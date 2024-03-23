/*
  Module kani waxa uu ka koobanyahay virtual machine
  kasoo execute gareenaayo each bytecode instruction one by one.
*/

#ifndef solo_vm_h
#define solo_vm_h

#include "chunk.h"
#include "value.h"



/*
  Result kasoo baxa virtual machine waa sadexdaan:
	1. INTERPRET_OK - waxay la micna tahay vurtual machine si seccessfully ah uyuu u execute gareeyay.
	2. INTERPRET_COMPILE_ERRRO - waxay la micna tahay inay dhacday compilation failure.
	3. INTERPRET_RUNTIME_ERROR - waxay la micno tahay inuu runtime error jiro.
*/
typedef enum{

	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR,
	INTERPRET_OK,

}InterpretResult;



/*
  @Description - virtual machine waa program ka execute gareenaayo bytecode ka.
  @length  -  waxa uu la socdaa inta elements ee ku jirto array daan.
  @capacity - waxa uu la socdaa inta  memory array box ee alocate gareesan.
  @stack   -  waa 'thick pointer'  array 
  @stackTop - waxaa ku keydsan top element of the stack.
  @ip  - waa program counter kaaso soo 'fetch' gareenaayo next instruction from the chunks.
*/
typedef struct{

	int length;
	int capacity;

	Value* stack;
	Value* stackTop;

	uint8_t*  ip;
	Chunk* chunk;
}VM;


/*
waxay initialize gareeneysaa virtual machine-ka
*/
void initVM();


/*
 push() - waxay ku push gareeneesaa Value to the stack.
*/
void push(Value value);

/*
pop() - waxay ka remove gareeneesaa Value from the stack kadibna, soo return gareenee.
*/
Value pop();


/*
waxa ay free gareeneysaa heap allocated memory kaaso stack isticmaalaayo.
*/
void freeStack(VM* vm);

/*
interpret() - waxay isku xireysaa pipelines.
*/
InterpretResult interpret(char* source);

/*
Markaan ka dhamaano isticmaal virtual machine-ka kadib waa free gareeneynaa.
*/
void freeVM();


#endif
