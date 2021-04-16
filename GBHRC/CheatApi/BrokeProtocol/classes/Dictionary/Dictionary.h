#pragma once
#include "../../Mono/Images/Script/ScriptImage.h"
#include <cstdint>

class Dictionary
{
public:
	char pad_0000[16]; //0x0000
	void* buckets; //0x0010
	Dictionary* entries; //0x0018
	void* comparer; //0x0020
	int64_t* keys; //0x0028
	int64_t* values; //0x0030
	int64_t* _syncRoot; //0x0038
	uint32_t count; //0x0040
	uint32_t version; //0x0044
	uint32_t freeList; //0x0048
	uint32_t freeCount; //0x004C

	void copy_to(Mono::MonoArray*array,int index);
};
