#pragma once
#include <cstdint>
#include "../../UnityTypes.h"

namespace BrokeProtocol
{
	class ShEquipable
	{
	public:
		char pad_0000[40]; //0x0000
		void* clEntity; //0x0028
		void* svEntity; //0x0030
		char pad_0038[52]; //0x0038
		uint32_t itemId; //0x006C
		char pad_0070[16]; //0x0070
		bool isHuman; //0x0080
		bool isWorldEntity; //0x0081
		bool hasInventory; //0x0082
		bool shop; //0x0083
		char pad_0084[8]; //0x0084
		int32_t ID; //0x008C
		uint32_t index; //0x0090
		int32_t value; //0x0094
		char pad_0098[136]; //0x0098
		uint32_t clipSize; //0x0120
		uint32_t currentClip; //0x0124
		char pad_0128[16]; //0x0128
		UnityTypes::String* itemName; //0x0138
		char pad_0140[8]; //0x0140
		void* ammoItem; //0x0148
		bool needItem; //0x0150
		bool illegal; //0x0151
		char pad_0152[2]; //0x0152
		float weight; //0x0154
		char pad_0158[8]; //0x0158
		float curMuzzle; //0x0160
		char pad_0164[24]; //0x0164
		float moveSpeed; //0x017C
		float accuracyFactor; //0x0180
		float recoilFactor; //0x0184
		float recoveryFactor; //0x0188
		char pad_018C[4]; //0x018C
	}; //Size: 0x0190

}
