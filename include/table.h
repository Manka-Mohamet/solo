#ifndef solo_table_h
#define solo_table_h

/*
  * Module-kan waxa uu ka koobanyahay HashTable ama HashMap
	kaaso aan u isticmaaleyno  variable name inaaan siino value inagoo isticmaaleyna key/value.

*/



#include "value.h"
#include "common.h"


// key pair value field as struct.
typedef struct{
	ObjString* key;
	Value value;

}Entry;



// array that holds key pair values
// haddii aad taqaano hashMap implementation kuma dhibeyso.
typedef struct{
	int capacity;
	int count;
	Entry* entries;


}Table;


// waxay initialize-gareeneysaa HashTable.
void initTable(Table* table);


// waxay free-gareeneysaa HashTable.
void freeTable(Table* table);


// waxay  binding kusameeneysaa given  key and  value.
bool tableSet(Table* table, ObjString* key, Value value);


// waxay hashTable ka search gareeneysaa value in a given key .
bool tableGet(Table* table, ObjString* key, Value value);


//waxay HashTable ka delete gareeneysaa value in a given key.
bool tableDel(Table* table, ObjString* key);


// waxay soo rareesaa dhamaan key/value from one HashTable to another.
void tableAddAll(Table* from, Table* to);

#endif
