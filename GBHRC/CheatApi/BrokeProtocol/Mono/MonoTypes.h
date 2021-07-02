#pragma once
#include <cstdint>

struct MonoInt
{
	char pad_0000[16]; //0x0000
	int32_t value; //0x0010
};

struct MonoByte
{
	char pad_0000[16]; //0x0000
	BYTE value; //0x0010
};

struct MonoBool
{
	char pad_0000[16]; //0x0000
	bool value; //0x0010
};

struct MonoFloat
{
	char pad_0000[16]; //0x0000
	float value; //0x0010
};
