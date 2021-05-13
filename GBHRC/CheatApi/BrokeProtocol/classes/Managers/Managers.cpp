#include "Managers.h"


#include "../../../../includes/logger.h"
#include "../../Mono/Mono.h"

UnityTypes::String* BrokeProtocol::Managers::ShManager::get_version()
{

	auto* mono_context = Mono::Context::get_context();

	static auto* getVerMethod = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		mono_context->mono_class_from_name(mono_context->get_script_image(), "BrokeProtocol.Managers", "ShManager"),
		"Version"
	));

	Mono::MonoObject* exc;
	return (UnityTypes::String*)mono_context->mono_runtime_invoke(getVerMethod, this, nullptr, &exc);
}
