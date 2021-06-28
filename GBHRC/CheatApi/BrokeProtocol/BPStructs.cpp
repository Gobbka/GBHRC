#include "BPStructs.h"

#include "Mono/MonoDefs.h"
#include "Mono/Images/Script/ScriptImage.h"

void BrokeProtocol::Structs::ClVehicle::MoveOn()
{
	auto* mono_context = Mono::Context::get_context();

	static Mono::MonoMethod* pMethod = Mono::ScriptImage::mono_get_method_from_name("BrokeProtocol.Entities.ClVehicle:MoveOn()", true);
	mono_context->mono_runtime_invoke(pMethod, this, nullptr, nullptr);
}
