#include "Players.h"

#include "../../../../includes/logger.h"
#include "../../Mono/Images/Script/ScriptImage.h"
#include "../Guns/ShEquipable.h"

#define STATIC_METHOD(name,inc_namespace) auto*mono_context=Mono::Context::get_context();static Mono::MonoMethod* pMethod =Mono::ScriptImage::mono_get_method_from_name(name, inc_namespace)

BrokeProtocol::ShEquipable* BrokeProtocol::Players::ShPlayer::current_weapon() const
{	
	return this->curEquipable;
}

void BrokeProtocol::Players::ShPlayer::set_position(UnityTypes::Vector3* position)
{
	// SetPosition
	STATIC_METHOD("BrokeProtocol.Entities.ShEntity:SetPosition(vector)", true);
	void* args[]{ position };
	mono_context->mono_runtime_invoke(pMethod, this, args, nullptr);
}

void BrokeProtocol::Players::ShPlayer::jump()
{
	STATIC_METHOD("BrokeProtocol.Entities.ShPlayer:Jump()", true);
	mono_context->mono_runtime_invoke(pMethod, this, nullptr, nullptr);
}

void BrokeProtocol::Players::ShPlayer::clear_injuries()
{
	STATIC_METHOD("BrokeProtocol.Entities.ShPlayer:ClearInjuries()", true);
	mono_context->mono_runtime_invoke(pMethod, this, nullptr, nullptr);
}

void BrokeProtocol::Players::ShPlayer::fire()
{
	STATIC_METHOD("BrokeProtocol.Entities.ShPlayer:Fire(int)", true);
	void* args[]{ &this->current_weapon()->index };
	mono_context->mono_runtime_invoke(pMethod, this, args, nullptr);
}

