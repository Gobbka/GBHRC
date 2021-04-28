#pragma once
#include <cstdint>

namespace UnityTypes
{
	class Vector3
	{
	public:
		char pad_0000[16]; //0x0000
		float x; //0x0010
		float y; //0x0014
		float z; //0x0018

		static Vector3* make(float x, float y, float z);
		float distanceTo(UnityTypes::Vector3* vector) const;
	};

	class String
	{
	public:
		char pad_0000[16]; //0x0000
		uint32_t length; //0x0010
		wchar_t  array[1]; //0x0014
	}; //Size: 0x004C	
}
