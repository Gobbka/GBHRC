#include "Players.h"

#include "../../../../includes/logger.h"
#include "../../Mono/Images/Script/ScriptImage.h"

#define STATIC_METHOD(name,inc_namespace) static Mono::MonoMethod* pMethod = Mono::ScriptImage::mono_get_method_from_name(name, inc_namespace)

BrokeProtocol::Structs::Equipable* BrokeProtocol::Players::ShPlayer::current_weapon() const
{	
	return this->curEquipable;
}

void BrokeProtocol::Players::ShPlayer::jump()
{
	STATIC_METHOD("BrokeProtocol.Entities.ShPlayer:Jump()", true);
	Mono::mono_runtime_invoke(pMethod, this, nullptr, nullptr);
}

void BrokeProtocol::Players::ShPlayer::clear_injuries()
{
	STATIC_METHOD("BrokeProtocol.Entities.ShPlayer:ClearInjuries()", true);
	Mono::mono_runtime_invoke(pMethod, this, nullptr, nullptr);
}

void BrokeProtocol::Players::ShPlayer::fire()
{
	STATIC_METHOD("BrokeProtocol.Entities.ShPlayer:Fire(int)", true);
	void* args[]{ &this->current_weapon()->index };
	Mono::mono_runtime_invoke(pMethod, this, args, nullptr);
}

UnityTypes::Vector3* BrokeProtocol::Players::ShPlayer::get_position() const
{
	static auto* pGetPosMethod = Mono::mono_property_get_get_method(Mono::mono_class_get_property_from_name(
		Mono::mono_class_from_name(Mono::get_UE_CoreModule(), "UnityEngine", "Transform"),
		"position"
	));
	
	return (UnityTypes::Vector3*)Mono::mono_runtime_invoke(pGetPosMethod, this->rotationT, nullptr, nullptr);
}

UnityTypes::Vector3* BrokeProtocol::Players::ShPlayer::get_eulerAngles() const
{
	static auto* pGetPosMethod = Mono::mono_property_get_get_method(Mono::mono_class_get_property_from_name(
		Mono::mono_class_from_name(Mono::get_UE_CoreModule(), "UnityEngine", "Transform"),
		"eulerAngles"
	));

	return (UnityTypes::Vector3*)Mono::mono_runtime_invoke(pGetPosMethod, this->rotationT, nullptr, nullptr);
}

//Matrix4X4* BrokeProtocol::Players::ShPlayer::get_worldToLocalMatrix() const
//{
//	static auto* pGetPosMethod = Mono::mono_property_get_get_method(Mono::mono_class_get_property_from_name(
//		Mono::mono_class_from_name(Mono::get_UE_CoreModule(), "UnityEngine", "Transform"),
//		"worldToLocalMatrix"
//	));
//	Mono::MonoObject* exc;
//	auto* matrix = (Matrix4X4*)
//		((size_t)Mono::mono_runtime_invoke(pGetPosMethod, this->rotationT, nullptr, &exc)+0x10);
//	if (exc != nullptr)
//		return nullptr;
//	return matrix;
//}
