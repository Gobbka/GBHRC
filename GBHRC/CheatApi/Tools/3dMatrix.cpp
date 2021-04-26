#include "3dMatrix.h"
#include <Windows.h>

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

bool WorldToScreen(Vector3 pos, POINT* screen, Matrix4X4* pmatrix, int windowWidth, int windowHeight)
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords

	Vector4 clipCoords;
	clipCoords.x = pos.x * pmatrix->m00 + pos.y * pmatrix->m01 + pos.z * pmatrix->m02 + pmatrix->m03;
	clipCoords.y = pos.x * pmatrix->m10 + pos.y * pmatrix->m11 + pos.z * pmatrix->m12 + pmatrix->m13;
	clipCoords.z = pos.x * pmatrix->m20 + pos.y * pmatrix->m21 + pos.z * pmatrix->m22 + pmatrix->m23;
	clipCoords.w = pos.x * pmatrix->m30 + pos.y * pmatrix->m31 + pos.z * pmatrix->m32 + pmatrix->m33;
	//clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
	//clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
	//clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
	//clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen->x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen->y = (windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}
