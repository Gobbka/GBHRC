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
	};

	class String
	{
	public:
		char pad_0000[16]; //0x0000
		uint32_t length; //0x0010
		wchar_t* pointer; //0x0014
		char pad_001C[48]; //0x001C
	}; //Size: 0x004C	
}
