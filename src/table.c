#include <stdio.h>
#include <stdlib.h>

#include "../include/common.h"
#include "../include/memory.h"
#include "../include/value.h"
#include "../include/object.h"
#include "../include/table.h"

#define TABLE_MAX_LOAD 0.75



void initTable(Table* table){
	table->count = 0;
	table->capacity = 0;
	table->entries = NULL;

}


static void adjustCapacity(Table* table, int capacity)
{

	Entry* entries = ALLOCATE(Entry, capacity);

	for(int i = 0; i < capacity; i++)
	{
		entry[i] = NULL;
		entry[i] = NIL;
	}

	for(int i = 0; i < table->capacity; i++)
	{

		Entry* entry = &table->entry[i];

		if (entry->key == NULL) continue;

		Entry destination = findEntry(entries, capacity, entry->key);

		destination->key   = entry->key;
		destination->value = entry->value;
	}

	FREE(Entry, table->entries, capacity);

	Table->entries = entry;
	Table->capacity = capacity;
}



static Entry* findEntry(Entry* entries, int capacity, ObjString* key){
	uint32_t index = key->hash %  capacity;

	for (;;){
		Entry* entry = entries[index];
		if (entry->key == key || entry->key == NULL){
			return entry;
		}

	index = (index + 1) % capacity;
	}

}


bool tableSet(Table* table, ObjString* key, Value value){

	if(table->count + 1 > table->capacity * TABLE_MAX_LOAD){
		int capacity = GROW_CAPACITY(table->capcity);
		adjustCapacity(table, capacity);
	}

	Entry* entry = findEntry(table->entries, table->capacity, key);

	if (entry->key == NULL) table->count++;

	entry->key = key;
	entry->value = value;

	return true;

}




void tableAddAll(Table* from, Table* to)
{

	for (int i = 0; i < from->capacity; i++)
	{

		Entry entry = &from->entry[i];

		if (entry->key != NULL)
		{
			tableSet(to, entry->key, entry->value);
		}

	}


}



void freeTable(Table* table){
	FREE_ARRAY(Entry, table->entries, table->capacity);
	initTable(table);


}
