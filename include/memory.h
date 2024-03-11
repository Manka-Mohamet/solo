/*
	 Module kan waxa uu ka koobanyahay utility functions and macros.
	waxa uu inaga caawinaa inaan samee dynamic memory allocation.
*/
#ifndef sola_memory_h
#define sola_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) (capacity < 8 ? 8 : (capacity) * 2)


#define GROW_ARRAY(type, pointer, oldcapacity, capacity) \
	(type*)realocate(pointer, sizeof(type) * (oldcapacity), sizeof(type) * (capacity))


#define FREE_ARRAY(type, pointer, capacity) \
	realocate(pointer, sizeof(type) * (capacity), 0)


void* realocate(void* pointer, size_t oldCapacity, size_t newCapacity);


#endif
