#ifndef solo_object_h
#define solo_object_h



#include "common.h"
#include "value.h"


#define IS_STRING(value) isObjectType(value, OBJ_STRING)
#define AS_OBJ(value) (AS_OBJ(value)->type)
#define AS_STRING(value) ((ObjString)AS_OBJ(value))
#define ASC_STRING(value)  ((ObjString*)AS_OBJ(value)->chars)




typedef enum{
	OBJ_STRING,

}ObjectType;





struct Obj{
	ObjectType type;
	struct Obj* next;

};




struct ObjString{
	struct Obj obj;
	int length;
	char* chars;
	uint32_t hash;

};

typedef struct ObjString ObjString;

ObjString* takeString(char* chars, int length);

void printObject(Value value);

ObjString* copyString(const char* chars, int length);

statid inline bool isObjType(Value value, ObjectType type){
	return IS_OBJ(value) && AS_OBJ(value)->type == type;
}



#endif
