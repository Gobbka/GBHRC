#pragma once
#include "ShEquipable.h"
#include <cstdint>

namespace BrokeProtocol
{
	struct ShBallistic : public ShEquipable
	{
	public:
		void* useSound; //0x0190
		int32_t burstSize; //0x0198
		float useDelay; //0x019C
		char pad_01A0[16]; //0x01A0
		uint32_t damageIndex; //0x01B0
		float range; //0x01B4
		char pad_01B8[16]; //0x01B8
		float damage; //0x01C8
		char pad_01CC[12]; //0x01CC
		void* reloadSound; //0x01D8
		float accuracy; //0x01E0
		float recoil; //0x01E4
		bool reloading; //0x01E8
		char pad_01E9[3]; //0x01E9
		float curRecoil; //0x01EC
		char pad_01F0[8]; //0x01F0
		float muzzleVelocity; //0x01F8
	}; //Size: 0x01FC
}

