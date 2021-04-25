#include "Players.h"

#include "../../../../includes/logger.h"
#include "../../Mono/Images/Script/ScriptImage.h"

#define STATIC_METHOD(name,inc_namespace) auto*mono_context=Mono::Context::get_context();static Mono::MonoMethod* pMethod =Mono::ScriptImage::mono_get_method_from_name(name, inc_namespace)

BrokeProtocol::Structs::Equipable* BrokeProtocol::Players::ShPlayer::current_weapon() const
{	
	return this->curEquipable;
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

