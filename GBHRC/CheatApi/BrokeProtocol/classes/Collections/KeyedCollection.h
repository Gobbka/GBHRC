#pragma once
#include "List.h"
#include "Dictionary.h"

namespace Collections {
	template<typename T>
	class KeyedCollection
	{
	public:
		char pad_0000[16]; //0x0000
		List<T>* items; //0x0010
		void* _syncRoot; //0x0018
		void* comparer; //0x0020
		Dictionary* dict; //0x0028
		uint32_t keyCount; //0x0030
		uint32_t threshold; //0x0034
	};
}
