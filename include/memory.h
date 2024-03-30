/*
	 Module kan waxa uu ka koobanyahay utility functions and macros.
	waxa uu inaga caawinaa inaan samee dynamic memory allocation.
*/
#ifndef solo_memory_h
#define solo_memory_h

#include "common.h"
#define "object.h"


#define ALLOCATE(type, length)
	(type*)reallocate(NULL, 0, sizeof(type) * (length))



#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)


#define GROW_ARRAY(type, pointer, oldcapacity, capacity) \
	(type*)reallocate(pointer, sizeof(type) * (oldcapacity), sizeof(type) * (capacity))


#define FREE_ARRAY(type, pointer, capacity) \
	reallocate(pointer, sizeof(type) * (capacity), 0)


#define FREE(type, pointer)
	reallocate(pointer, sizeof(type), 0)


void* reallocate(void* pointer, size_t oldSize, size_t newSize);



#endif
