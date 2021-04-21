#pragma once
#include "../../BPStructs.h"
#include "../Transform/Transform.h"

namespace BrokeProtocol
{
	namespace Players {
		class ShPlayer
		{
		public:

			char pad_0000[140]; //0x0000
			uint32_t ID; //0x008C
			char pad_0090[168]; //0x0090
			float health; //0x0138
			float healthLimit; //0x013C
			char pad_0140[72]; //0x0140
			float speed; //0x0188
			float speedLimit; //0x018C
			Transform* rotationT; //0x0190
			class ClPlayer* clPlayer; //0x0198
			void* svPlayer; //0x01A0
			void* specPlayer; //0x01A8
			Structs::String* username; //0x01B0
			void* displayName; //0x01B8
			void* wearableOptions; //0x01C0
			void* capsule; //0x01C8
			char pad_01D0[8]; //0x01D0
			Structs::Equipable* curEquipable; //0x01D8
			char pad_01E0[32]; //0x01E0
			class Mountable* curMount; //0x0200
			char pad_0208[56]; //0x0208
			uint32_t ground; //0x0240
			uint32_t moveMode; //0x0244
			char pad_0248[40]; //0x0248
			class Location* Location; //0x0270
			uint32_t boss; //0x0278
			char pad_027C[12]; //0x027C
			bool mode; //0x0288
			bool pointing; //0x0289
			char pad_028A[2]; //0x028A
			uint32_t armorLevel; //0x028C
			bool lockedTrade; //0x0290
			bool switching; //0x0291
			char pad_0292[2]; //0x0292
			uint32_t wantedLevel; //0x0294
			float wantedNormalized; //0x0298
			uint32_t experience; //0x029C
			uint32_t rank; //0x02A0
			char pad_02A4[20]; //0x02A4
			uint32_t fireIndex; //0x02B8
			char pad_02BC[12]; //0x02BC
			float weigth; //0x02C8
			float weightLimit; //0x02CC



		public:

			Structs::Equipable* current_weapon() const;

			void jump();
			void clear_injuries();
			void fire();

			Structs::Vector3* get_position() const;
			Structs::Vector3* get_eulerAngles() const;
			Structs::Matrix4X4* get_worldToLocalMatrix() const;
		};

		class ClPlayer
		{
		public:
			char pad_0000[48]; //0x0000
			class ClManager* clManager; //0x0030
			char pad_0038[212]; //0x0038
		}; //Size: 0x010C
	}
}
