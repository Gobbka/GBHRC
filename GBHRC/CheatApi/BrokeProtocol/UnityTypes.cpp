#include "UnityTypes.h"

#include "../../includes/logger.h"
#include "Mono/Mono.h"

#define STATIC_METHOD(name,inc_namespace,param_count) static Mono::MonoMethod* pMethod = Mono::mono_get_method_from_image(Mono::get_UE_CoreModule(),name, inc_namespace,param_count)

UnityTypes::Vector3* UnityTypes::Vector3::make(float x, float y, float z)
{
	auto* mono_context = Mono::Context::get_context();
	auto* vector = (Vector3*)mono_context->mono_object_new(mono_context->mono_get_root_domain(), mono_context->mono_class_from_name(mono_context->get_UE_CoreModule(), "UnityEngine", "Vector3"));
	vector->x = x; vector->y = y; vector->z = z;
	return vector;
}

float UnityTypes::Vector3::distanceTo(UnityTypes::Vector3* vector) const
{
	return sqrt(pow(vector->x - this->x, 2) + pow(vector->y - this->y, 2) + pow(vector->z - this->z, 2));
}

void UnityTypes::RigidBody::set_position(UnityTypes::Vector3* vector)
{
	auto mono_context = Mono::Context::get_context();
	
	static auto* set_method = mono_context->mono_property_get_set_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_physic_image(), "UnityEngine", "Rigidbody"),
		"position"
	));
	void* params[]{ vector };
	mono_context->mono_runtime_invoke(set_method, this, params, nullptr);
}

UnityTypes::Vector3* UnityTypes::RigidBody::get_position()
{
	auto mono_context = Mono::Context::get_context();

	static auto* get_method = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_physic_image(), "UnityEngine", "Rigidbody"),
		"position"
	));

	return (Vector3*)mono_context->mono_runtime_invoke(get_method, this, nullptr, nullptr);
}

void UnityTypes::RigidBody::set_use_gravity(bool use)
{
	auto mono_context = Mono::Context::get_context();

	static auto* set_method = mono_context->mono_property_get_set_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_physic_image(), "UnityEngine", "Rigidbody"),
		"useGravity"
	));
	void* params[]{ &use };
	mono_context->mono_runtime_invoke(set_method, this, params, nullptr);
}

void UnityTypes::RigidBody::set_mass(float mass)
{
	auto mono_context = Mono::Context::get_context();

	static auto* set_method = mono_context->mono_property_get_set_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_physic_image(), "UnityEngine", "Rigidbody"),
		"mass"
	));
	void* params[]{ &mass };
	mono_context->mono_runtime_invoke(set_method, this, params, nullptr);
}

void UnityTypes::RigidBody::MovePosition(UnityTypes::Vector3* vector)
{
	auto* mono_context = Mono::Context::get_context();
	static Mono::MonoMethod* pMethod = mono_context->mono_get_method_from_image(mono_context->get_physic_image(), "UnityEngine.Rigidbody:MovePosition(vector)", true, 1);
	void* params[]{ vector };
	mono_context->mono_runtime_invoke(pMethod, this, params, nullptr);
}

void UnityTypes::RigidBody::add_force(UnityTypes::Vector3* vector)
{
	auto* mono_context = Mono::Context::get_context();
	static Mono::MonoMethod* pMethod = mono_context->mono_get_method_from_image(mono_context->get_physic_image(), "UnityEngine.Rigidbody:AddForce(vector)", true, 1);
	void* params[]{ vector };
	mono_context->mono_runtime_invoke(pMethod, this, params, nullptr);
}

void UnityTypes::RigidBody::add_force(float x, float y, float z)
{
	//AddForce
	auto* mono_context = Mono::Context::get_context();
	static Mono::MonoMethod* pMethod = mono_context->mono_get_method_from_image(mono_context->get_physic_image(), "UnityEngine.Rigidbody:AddForce(float,float,float)", true, 4);
	int nigga = 0x2; // VelocityChange
	void* params[]{ &x,&y,&z,&nigga };
	mono_context->mono_runtime_invoke(pMethod, this, params, nullptr);
}

