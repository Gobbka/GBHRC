#include "3dMatrix.h"
#include <Windows.h>

Vector3 WorldToScreen(Vector3 pos, Matrix4X4* pmatrix, RECT clientrect)
{
	float _x = pmatrix->m00 * pos.x + pmatrix->m01 * pos.y + pmatrix->m02 * pos.z + pmatrix->m03;
	float _y = pmatrix->m10 * pos.x + pmatrix->m11 * pos.y + pmatrix->m12 * pos.z + pmatrix->m13;
	float w  = pmatrix->m30 * pos.x + pmatrix->m31 * pos.y + pmatrix->m32 * pos.z + pmatrix->m33;

	float inv_w = 1.f / w;
	_x *= inv_w;
	_y *= inv_w;

	int height = (clientrect.right - clientrect.left);
	int width = (clientrect.bottom - clientrect.top);
	POINT center{ width / 2,height / 2 };
	
	float x = center.x * .5f * _x + .5f;
	float y = center.y * .5f * _y + .5f;

	return { x,y,w };
}
