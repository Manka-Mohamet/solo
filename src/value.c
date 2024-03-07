#include <stdlib.h>

#include "../include/value.h"
#include "../include/memory.h"


void initValueArray(ValueArray* array){
	array->length = 0;
	array->capacity = 0;
	array->values = NULL;

}



void writeValueArray(ValueArray* array, Value value){
	if ( array->length + 1 > array->capacity){
		int capacity = GROW_CAPACITY(array->capacity);
		array->values = GROW_ARRAY(Value, array, array->capacity, capacity);
	}

	array->values[array->length] = value
	array->length++;
}




void freeValueArray(ValueArray* array){
	FREE_ARRAY(array->values);
	initValueArray(array->values);

}
