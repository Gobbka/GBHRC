#pragma once

struct Vector3
{
	float x, y, z;
};

struct Matrix4X4
{
	float matrix[4][4];
};

Vector3 WorldToScreen(Vector3 pos, Matrix4X4* pmatrix);
