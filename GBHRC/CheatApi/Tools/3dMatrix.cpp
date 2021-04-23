#include "3dMatrix.h"
#include <Windows.h>

Vector3 WorldToScreen(Vector3 pos, Matrix4X4* pmatrix)
{
	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);

	Vector4 clip;
	clip.x = pos.x * pmatrix->m00 + pos.y * pmatrix->m01 * pos.z * pmatrix->m02 + pmatrix->m03;
	clip.y = pos.x * pmatrix->m10 + pos.y * pmatrix->m11 * pos.z * pmatrix->m12 + pmatrix->m13;
	clip.z = pos.x * pmatrix->m20 + pos.y * pmatrix->m21 * pos.z * pmatrix->m22 + pmatrix->m23;
	clip.w = pos.x * pmatrix->m30 + pos.y * pmatrix->m31 * pos.z * pmatrix->m32 + pmatrix->m33;
	if (clip.w < 0.1f)
		return { 0,0,-1 };

	Vector3 ndc;
	ndc.x = clip.x / clip.w;
	ndc.y = clip.y / clip.w;
	ndc.z = clip.z / clip.w;

	return ndc;
}
