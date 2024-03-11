#include <stdlib.h>

#include "../include/memory.h"


void* realocate(void* pointer, size_t oldCapacity, size_t newCapacity){
	if (newCapacity == 0){
		free(pointer);
		return NULL;
	}

 	void* result = realloc(pointer, newCapacity);
	return result;

}
