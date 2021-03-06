#pragma once
#include "../../Mono/Images/Script/ScriptImage.h"
#include <cstdint>

#include "List.h"

namespace Collections
{
	class Dictionary;

	class Entry
	{
	public:
		char pad_0000[16]; //0x0000
		uint32_t hashcode; //0x0010
		uint32_t next; //0x0014
		void* key; //0x0018
		void* value; //0x0020
	};
	
	class Enumerator
	{
	public:
		char pad_0000[16]; //0x0000
		Dictionary* dictionary; //0x0010
		int version; //0x0018
		uint32_t index; //0x001C
		void* PairKey; //0x0020
		void* PairValue; //0x0028

		bool MoveNext();
		void reset();
		void* current();
		Entry* entry();
	};

	class ValueCollection
	{
	public:
		Enumerator* get_enumerator();
		Mono::MonoArray* to_array();
		void copy_to(Mono::MonoArray* array, int index);

		int count();
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
		int version; //0x0044
		uint32_t freeList; //0x0048
		uint32_t freeCount; //0x004C

		int FindEntry(int key);
		void copy_to(Mono::MonoArray* array, int index);
		bool contains(void* item);
		void clear();

		ValueCollection* get_values();
		Enumerator* get_enumerator();
	};
}