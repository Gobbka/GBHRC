#pragma once
#include <Windows.h>

struct Vector4
{
	float x, y, z,w;
};

struct Vector3
{
	float x, y, z;
};

struct Matrix4X4
{
	char pad_0000[16]; //0x0000
		float m00; //0x0010
		float m10; //0x0014
		float m20; //0x0018
		float m30; //0x001C
		float m01; //0x0020
		float m11; //0x0024
		float m21; //0x0028
		float m31; //0x002C
		float m02; //0x0030
		float m12; //0x0034
		float m22; //0x0038
		float m32; //0x003C
		float m03; //0x0040
		float m13; //0x0044
		float m23; //0x0048
		float m33; //0x004C

		void mul(Matrix4X4* matrix);
		Vector3 multiply(Vector3 vector);
};

/// <summary>
/// DEPRECATED
/// </summary>
/// <param name="pos"></param>
/// <param name="pmatrix"></param>
/// <param name="clientrect"></param>
/// <returns></returns>
Vector3 WorldToScreen(Vector3 pos, Matrix4X4* pmatrix,RECT clientrect);


