#pragma once
#include <cstdint>
namespace Collections {
	template<typename T>
	class List
	{
	public:
		char pad_0000[16]; //0x0000
		T* _items; //0x0010
		uint32_t _size; //0x0018
		uint32_t _version; //0x001C
	};
}