#include <stdio.h>
#include <stdlib.h>

#include "../include/common.h"
#include "../include/memory.h"
#include "../include/value.h"
#include "../include/object.h"
#include "../include/table.h"


void initTable(Table* table){
	table->count = 0;
	table->capacity = 0;
	table->entries = NULL;

}


bool tableSet(Table* table, ObjString* key, Value value){
	Entry* entry = findEntry(table->entries, table->capacity, key);
	if (entry->key == NULL) table->count++;
	entry->key = key;
	entry->value = value;

	return true;

}



void freeTable(Table* table){
	FREE_ARRAY(Entry, table->entries, table->capacity);
	initTable(table);


}
