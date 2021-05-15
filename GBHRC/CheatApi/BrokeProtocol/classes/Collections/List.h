#pragma once
#include <cstdint>

#include "../../../../includes/logger.h"

namespace Collections {

	template<typename T>
	class Iterator
	{
		int size;
		T* pointer;
		int iteration;
	public:
		Iterator(int _size, T* ptr)
		{
			this->size = _size;
			this->pointer = ptr;
			this->iteration = -1;
		}

		void reset()
		{
			this->iteration = -1;
		}

		bool next()
		{
			if (iteration < size-1)
			{
				iteration++;
				return true;
			}
			return false;
		}

		T item()
		{
			return this->pointer[iteration];
		}
	};
	
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

		Iterator<T> iterator()
		{
			return Iterator<T>(_size, this->pointer());
		}

		auto size()
		{
			return this->_size;
		}
	};


}
