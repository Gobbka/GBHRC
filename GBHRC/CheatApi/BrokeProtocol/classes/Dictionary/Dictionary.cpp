#include "Dictionary.h"
#include "../../BrokeProtocol.h"
#include "../../../../includes/logger.h"

void Dictionary::copy_to(Mono::MonoArray* array, int index)
{
	void* args[1];
	args[0] = BrokeProtocol::GetLocalPlayer();

	auto* klass = Mono::mono_object_get_class((Mono::MonoObject*)this);

	DEBUG_LOG("KLASS: " << klass);
	if (klass == nullptr)
		return;
	
	auto* method = Mono::mono_class_get_method_from_name(
		klass,
		"ContainsValue",
		-1
	);

	DEBUG_LOG("METHOD:"<<method);
	Mono::mono_thread_attach(Mono::mono_get_root_domain());
	Mono::MonoObject* exception;
	bool cont = (bool)Mono::mono_runtime_invoke(
		method,
		this,
		args,
		&exception
	);
	if(exception!=nullptr)
	{
		DEBUG_LOG("NIGGER ERROR");
		Mono::mono_print_unhandled_exception(exception);
	}else
	{
		if (cont)
			DEBUG_LOG("CONTAINS");
		else
			DEBUG_LOG("NIGGER DOES NOT EXIST");
	}
}

bool Dictionary::contains(void* item)
{
	void* args[1]{ item };
	auto* method = Mono::mono_class_get_method_from_name(
		Mono::mono_object_get_class((Mono::MonoObject*)this),
		"ContainsValue",-1
	);
	return (bool)Mono::mono_runtime_invoke(method, this, args, nullptr);
}
