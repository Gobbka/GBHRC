#include "3dMatrix.h"

Vector3 WorldToScreen(Vector3 pos, Matrix4X4* pmatrix)
{
	auto matrix = pmatrix->matrix;
	float _x = matrix[0][0] * pos.x + matrix[0][1] * pos.y + matrix[0][2] * pos.z + matrix[0][3];
	float _y = matrix[1][0] * pos.x + matrix[1][1] * pos.y + matrix[1][2] * pos.z + matrix[1][3];
	float w = matrix[3][0] * pos.x + matrix[3][1] * pos.y + matrix[3][2] * pos.z + matrix[3][3];

	float inv_w = 1.f / w;
	_x *= inv_w;
	_y *= inv_w;

	float x = 0;
	float y = 0;

	x += 0.5f * _x + 0.5f;
	y += 0.5f * _y + 0.5f;

	return { x, y,w };
}
