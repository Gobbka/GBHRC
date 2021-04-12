#pragma once
#include <cstdint>
// Created with ReClass.NET 1.2 by KN4CK3R

enum class MoveState : int32_t
{
	CantMove = 2,
	Running = 0,
	Walking = 0
};

class ClPlayer
{
public:
	char pad_0000[304]; //0x0000
	float Health; //0x0130
	float MaxHealth; //0x0134
	char pad_0138[48]; //0x0138
	bool isMoving; //0x0168
	char pad_0169[23]; //0x0169
	float StartSpeed; //0x0180
	float MaxWalkSpeed; //0x0184
	char pad_0188[80]; //0x0188
	class PlayerHand* HandItem; //0x01D8
	char pad_01E0[24]; //0x01E0
	class MountableEntity* MountedEntityPtr; //0x01F8
	char pad_0200[112]; //0x0200
	class Location* LocationPtr; //0x0270
	int32_t EntityType; //0x0278
	float GoingForward; //0x027C
	float UnknownStat; //0x0280
	float GoingLeft; //0x0284
	MoveState State; //0x0288
	char pad_028C[5]; //0x028C
	bool Switching; //0x0291
	char pad_0292[2]; //0x0292
	int32_t WantedLevel; //0x0294
	float WanderNormalized; //0x0298
	uint32_t Expirience; //0x029C
	int32_t Rank; //0x02A0
	char pad_02A4[5]; //0x02A4
	bool OnGround; //0x02A9
	char pad_02AA[30]; //0x02AA
	float Weight; //0x02C8
	float WeightLimit; //0x02CC
}; //Size: 0x02D0

class Location
{
public:
	char pad_0000[32]; //0x0000
	float Ox; //0x0020
	float Oy; //0x0024
	float Oz; //0x0028
}; //Size: 0x002C

class PlayerHand
{
public:
	char pad_0000[100]; //0x0000
	int32_t ItemId; //0x0064
	char pad_0068[40]; //0x0068
}; //Size: 0x0090

class MountableEntity
{
public:
	char pad_0000[304]; //0x0000
	float Health; //0x0130
	float MaxHealth; //0x0134
	char pad_0138[72]; //0x0138
	float MaxSpeed; //0x0180
	char pad_0184[40]; //0x0184
	int32_t SteerengWheels; //0x01AC
	float Speed; //0x01B0
	float WheelRotationAngle; //0x01B4
	char pad_01B8[4]; //0x01B8
	float Gas; //0x01BC
	char pad_01C0[8]; //0x01C0
}; //Size: 0x01C8