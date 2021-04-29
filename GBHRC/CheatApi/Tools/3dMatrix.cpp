#include "3dMatrix.h"
#include <Windows.h>

void Matrix4X4::mul(Matrix4X4* matrix)
{
	this->m00 *= matrix->m00;
	this->m10 *= matrix->m10;
	this->m20 *= matrix->m20;
	this->m30 *= matrix->m30;
	this->m01 *= matrix->m01;
	this->m11 *= matrix->m11;
	this->m21 *= matrix->m21;
	this->m31 *= matrix->m31;
	this->m02 *= matrix->m02;
	this->m12 *= matrix->m12;
	this->m22 *= matrix->m22;
	this->m32 *= matrix->m32;
	this->m03 *= matrix->m03;
	this->m13 *= matrix->m13;
	this->m23 *= matrix->m23;
	this->m33 *= matrix->m33;
}

Vector3 Matrix4X4::multiply(Vector3 pos)
{
	Vector3 clipCoords{};
	auto* pmatrix = this;
	clipCoords.x = pos.x * pmatrix->m00 + pos.y * pmatrix->m01 + pos.z * pmatrix->m02 + pmatrix->m03;
	clipCoords.y = pos.x * pmatrix->m10 + pos.y * pmatrix->m11 + pos.z * pmatrix->m12 + pmatrix->m13;
	clipCoords.z = pos.x * pmatrix->m20 + pos.y * pmatrix->m21 + pos.z * pmatrix->m22 + pmatrix->m23;
	return clipCoords;
}

Vector3 WorldToScreen(Vector3 pos, Matrix4X4* pmatrix, RECT clientrect)
{
	//float _x = pmatrix->m00 * pos.x + pmatrix->m01 * pos.y + pmatrix->m02 * pos.z + pmatrix->m03;
	//float _y = pmatrix->m10 * pos.x + pmatrix->m11 * pos.y + pmatrix->m12 * pos.z + pmatrix->m13;
	//float w  = pmatrix->m30 * pos.x + pmatrix->m31 * pos.y + pmatrix->m32 * pos.z + pmatrix->m33;

	//float inv_w = 1.f / w;
	//_x *= inv_w;
	//_y *= inv_w;
	//
	//float x = .5f * _x + .5f;
	//float y = .5f * _y + .5f;

	//return { x,y,w };
	return { 0,0,0 };
}
