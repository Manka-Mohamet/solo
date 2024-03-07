/*
	 Module kan waxa uu ka koobanyahay utility functions and macros.
	waxa uu inaga caawinaa inaan samee dynamic memory allocation.
*/
#ifndef sola_memory_h
#define sola_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) (capacity < 8 ? 8 : (capacity) * 2)


#define GROW_ARRAY(type, pointer, oldCapacity, newCapacity) 
	(type*)realocate(pointer, sizeof(type) * (oldCapacity), sizeof(type) * newCapacity)


#define FREE_ARRAY(type, pointer oldCapacity)
	(type*)realocate(pointer, sizeof(type) * (oldCapacity), sizeof(type) * (newCapacity), 0)


void* realocate(void* pointer, size_t oldCapacity, size_t newCapacity);


#endif
