#include "3dMatrix.h"
#include <Windows.h>


#include "../../includes/logger.h"
#include "../BrokeProtocol/Mono/Mono.h"
#include "Render/Render.h"

void Matrix4X4::mul(Matrix4X4* matrix)
{
	float* other_matrix = &matrix->m00;
	float* my_matrix = &this->m00;
	for(int i = 0;i < 16;i++)
	{
		if(other_matrix[i]!=0.f)
			my_matrix[i] *= other_matrix[i];
	}
	return;
	
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

Vector4 Matrix4X4::multiply(Vector4 pos)
{
	Vector4 clipCoords{};
	auto* pmatrix = this;
	clipCoords.x = pos.x * pmatrix->m00 + pos.y * pmatrix->m01 + pos.z * pmatrix->m02 + pos.w*pmatrix->m03;
	clipCoords.y = pos.x * pmatrix->m10 + pos.y * pmatrix->m11 + pos.z * pmatrix->m12 + pos.w*pmatrix->m13;
	clipCoords.z = pos.x * pmatrix->m20 + pos.y * pmatrix->m21 + pos.z * pmatrix->m22 + pos.w*pmatrix->m23;
	clipCoords.w = pos.x * pmatrix->m30 + pos.y * pmatrix->m31 + pos.z * pmatrix->m32 + pos.w*pmatrix->m33;
	return clipCoords;
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

Matrix4X4* Matrix4X4::inverse()
{
	auto* mono_context = Mono::Context::get_context();

	static auto* pSetPosMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Matrix4x4"),
		"inverse"
	));

	return (Matrix4X4*)mono_context->mono_runtime_invoke(pSetPosMethod, this, nullptr, nullptr);
}

void Matrix4X4::dump()
{
	DEBUG_LOG(
		this->m00 << " " << this->m01 << " " << this->m02 << " " << this->m03 << "\n" <<
		this->m10 << " " << this->m11 << " " << this->m12 << " " << this->m13 << "\n" <<
		this->m20 << " " << this->m21 << " " << this->m22 << " " << this->m23 << "\n" <<
		this->m30 << " " << this->m31 << " " << this->m32 << " " << this->m33
	
	);
}

Vector3 Matrix4X4::worldToScreen(Matrix4X4* view_matrix, Matrix4X4* projection_matrix, Vector3 pos,Application::Render::Resolution windowSize)
{

	auto clipCoords = view_matrix->multiply(Vector4{ pos.x,pos.y,pos.z,1.0 });
	clipCoords = projection_matrix->multiply(clipCoords);

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;

	Vector3 screen;

	screen.x = ((float)windowSize.width / 2 * NDC.x);
	screen.y = ((float)windowSize.height / 2 * NDC.y);
	screen.z = clipCoords.w;

	return screen;
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
