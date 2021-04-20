#pragma once
#include "../../Mono/Images/Script/ScriptImage.h"
#include <cstdint>

class Dictionary;

class Enumerator
{
public:
	char pad_0000[16]; //0x0000
	Dictionary* dictionary; //0x0010
	uint32_t version; //0x0018
	uint32_t index; //0x001C
	void* PairKey; //0x0020
	void* PairValue; //0x0028
	
	bool MoveNext();
};

class Entry
{
public:
	char pad_0000[16]; //0x0000
	uint32_t hashcode; //0x0010
	uint32_t next; //0x0014
	void* key; //0x0018
	void* value; //0x0020
};

class List
{
public:
	char pad_0000[16]; //0x0000
	void** _items; //0x0010
	uint32_t _size; //0x0018
	uint32_t _version; //0x001C
};

class KeyedCollection
{
public:
	char pad_0000[16]; //0x0000
	List* items; //0x0010
	void* _syncRoot; //0x0018
	void* comparer; //0x0020
	Dictionary* dict; //0x0028
	uint32_t keyCount; //0x0030
	uint32_t threshold; //0x0034
};

class Dictionary
{
public:
	char pad_0000[16]; //0x0000
	void* buckets; //0x0010
	Entry** entries; //0x0018
	void* comparer; //0x0020
	int64_t* keys; //0x0028
	int64_t* values; //0x0030
	int64_t* _syncRoot; //0x0038
	uint32_t count; //0x0040
	uint32_t version; //0x0044
	uint32_t freeList; //0x0048
	uint32_t freeCount; //0x004C

	int FindEntry(int key);
	void copy_to(Mono::MonoArray*array,int index);
	bool contains(void* item);
	void clear();
	Enumerator* get_enumerator();
};


