#pragma once
#include "../../BPStructs.h"
#include "../Guns/ShEquipable.h"

namespace BrokeProtocol
{
	namespace Players {
		enum class CharacterType : int32_t
		{
			All = -1,
			Human = 0,
			Mob = 1
		};

		class ShMovable
		{
		public:
			char pad_0000[24]; //0x0000
			void* mainT; //0x0018
			char pad_0020[108]; //0x0020
			uint32_t ID; //0x008C
			char pad_0090[168]; //0x0090
			float health; //0x0138
			float healthLimit; //0x013C
			char pad_0140[16]; //0x0140
			UnityTypes::RigidBody* positionRB; //0x0150
			char pad_0158[48]; //0x0158
			float speed; //0x0188
			float speedLimit; //0x018C
		}; //Size: 0x0190

		
		class ShPlayer : public ShMovable
		{
		public:
			Structs::StanceType* stances; //0x0190
			UnityEngine::Transform* rotationT; //0x0198
			ClPlayer* clPlayer; //0x01A0
			void* svPlayer; //0x01A8
			UnityTypes::String* hands; //0x01B0
			UnityTypes::String* surrender; //0x01B8
			void* specPlayer; //0x01C0
			UnityTypes::String* username; //0x01C8
			void* displayName; //0x01D0
			void* wearableOptions; //0x01D8
			void* capsule; //0x01E0
			char pad_01E8[8]; //0x01E8
			void* (*bindings)[2]; //0x01F0
			ShEquipable* curEquipable; //0x01F8
			class Wearable* curWearables; //0x0200
			char pad_0208[16]; //0x0208
			ShMovable* curMount; //0x0218
			char pad_0220[8]; //0x0220
			Structs::StanceType* stance; //0x0228
			char pad_0230[16]; //0x0230
			float(*stats)[3]; //0x0240
			char pad_0248[16]; //0x0248
			uint32_t ground; //0x0258
			char pad_025C[44]; //0x025C
			class Location* Location; //0x0288
			CharacterType CharacterType; //0x0290
			uint32_t boss; //0x0294
			char pad_0298[12]; //0x0298
			bool mode; //0x02A4
			bool pointing; //0x02A5
			char pad_02A6[2]; //0x02A6
			uint32_t armorLevel; //0x02A8
			bool lockedTrade; //0x02AC
			bool switching; //0x02AD
			char pad_02AE[2]; //0x02AE
			uint32_t wantedLevel; //0x02B0
			float wantedNormalized; //0x02B4
			uint32_t experience; //0x02B8
			uint32_t rank; //0x02BC
			char pad_02C0[20]; //0x02C0
			uint32_t fireIndex; //0x02D4
			char pad_02D8[12]; //0x02D8
			float weigth; //0x02E4
			float weightLimit; //0x02E8
			char pad_02EC[8]; //0x02EC
		public:

			ShEquipable* current_weapon() const;

			void set_position(UnityTypes::Vector3* position);
			void jump();
			void clear_injuries();
			void fire();
		};

		class ClPlayer
		{
		public:
			char pad_0000[48]; //0x0000
			Managers::ClManager* clManager; //0x0030
			char pad_0038[212]; //0x0038
		}; //Size: 0x010C
	}
}
