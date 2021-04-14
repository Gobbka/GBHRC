#include <cstdint>

class ShPlayer
{
public:
	char pad_0000[132]; //0x0000
	uint32_t ID; //0x0084
	char pad_0088[168]; //0x0088
	float health; //0x0130
	float healthLimit; //0x0134
	char pad_0138[72]; //0x0138
	float speed; //0x0180
	float speedLimit; //0x0184
	void* rotationT; //0x0188
	class ClPlayer* clPlayer; //0x0190
	void* svPlayer; //0x0198
	void* specPlayer; //0x01A0
	class String* username; //0x01A8
	void* displayName; //0x01B0
	void* wearableOptions; //0x01B8
	void* capsule; //0x01C0
	char pad_01C8[16]; //0x01C8
	class Equipable* curEquipable; //0x01D8
	char pad_01E0[24]; //0x01E0
	class Mountable* curMount; //0x01F8
	char pad_0200[64]; //0x0200
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
	char pad_02D0[16]; //0x02D0


	Equipable* current_weapon() const
	{
		return this->curEquipable;
	}
}; //Size: 0x02E0

class String
{
public:
	char pad_0000[16]; //0x0000
	uint32_t length; //0x0010
	wchar_t* pointer; //0x0014
	char pad_001C[48]; //0x001C
}; //Size: 0x004C

class Location
{
public:
	char pad_0000[32]; //0x0000
	float oX; //0x0020
	float oY; //0x0024
	float oZ; //0x0028
	char pad_002C[28]; //0x002C
}; //Size: 0x0048

class Mountable
{
public:
	char pad_0000[304]; //0x0000
	float health; //0x0130
	float maxHealth; //0x0134
	char pad_0138[72]; //0x0138
	float maxSpeed; //0x0180
	char pad_0184[132]; //0x0184
}; //Size: 0x0208

class Equipable
{
public:
	char pad_0000[32]; //0x0000
	void* clEntity; //0x0020
	void* svEntity; //0x0028
	char pad_0030[60]; //0x0030
	uint32_t itemId; //0x006C
	char pad_0070[16]; //0x0070
	bool isHuman; //0x0080
	bool isWorldEntity; //0x0081
	bool hasInventory; //0x0082
	bool shop; //0x0083
	uint32_t ID; //0x0084
	uint32_t index; //0x0088
	int32_t Value; //0x008C
	char pad_0090[144]; //0x0090
	uint32_t cannot_shoot; //0x0120
	char pad_0124[156]; //0x0124
	uint32_t damage; //0x01C0
	char pad_01C4[8]; //0x01C4
}; //Size: 0x01CC

class ClPlayer
{
public:
	char pad_0000[48]; //0x0000
	void* clManager; //0x0030
	char pad_0038[212]; //0x0038
}; //Size: 0x010C