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

void BrokeProtocol::Managers::SearchingMenu::take_amount(int index, int amount)
{
	auto* mono_context = Mono::Context::get_context();
	auto* nigger = mono_context->mono_object_get_class((Mono::MonoObject*)this);
	static auto*method = mono_context->mono_class_get_method_from_name(nigger, "TakeAmount", -1);
	
	DEBUG_LOG("METHOD TAKE: " << method);
	void* param[]{&index,&amount};
	Mono::MonoObject* exc;
	mono_context->mono_runtime_invoke(method, this, param, &exc);

	if(exc != nullptr)
	{
		mono_context->mono_print_system_exception(exc);
		DEBUG_LOG("");
	}
}
