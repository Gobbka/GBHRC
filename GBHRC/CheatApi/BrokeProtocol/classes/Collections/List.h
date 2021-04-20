#pragma once
#include <cstdint>
namespace Collections {
	template<typename T>
	class List
	{
	private:
		char pad_0000[16]; //0x0000
		void* _items; //0x0010
		uint32_t _size; //0x0018
		uint32_t _version; //0x001C
	public:
		T* pointer()
		{
			// we make offset 0x20 cos its c# array
			return (T*)((size_t)this->_items + 0x20);
		}

		auto size()
		{
			return this->_size;
		}
	};
}