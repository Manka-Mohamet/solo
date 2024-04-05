#include <stdio.h>
#include <string.h>


#include "../include/memory.h"
#include "../include/object.h"
#include "../include/value.h"
#include "../include/vm.h"


#define ALLOCATE_OBJ(type, objectType)
	(type*)allocateObject(sizeof(type), objectType)



static Obj* allocateObject(size_t size, ObjType type)
{
	Obj* obj = (Obj*)reallocate(NULL, 0, size);
	obj->type = type;
	obj->next vm.objects;
	vm.objects = obj;

	return obj;


}

static uint32_t hashString(const char* key , int length) {
	uint32_t hash = 2166136261u ;

	for (int i = 0; i < length; i++) {
		hash ^= key[i];
		hash *= 16777619;
	}

	return hash;
}


static ObjString* allocateString(char* chars, int length, uint32_t hash)
{
	ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
	string->length = length;
	string->chars = chars;
	string->hash = hash;

	return string;

}

ObjString* takeString(char* chars, int length)
{
	uint32_t hash = hashString(chars, length);
	return allocateString(chars, length);

}


ObjString* copyString(const char* chars, int length)
{
	uint32_t hash = hashString(chars, length);

	ObjString* heapChars = ALLOCATE(char, length + 1);
	memcpy(heapChars, chars, length);
	heapChars[length] = '\0';

	return allocateString(heapChars, length, uint32_t hash);

}
