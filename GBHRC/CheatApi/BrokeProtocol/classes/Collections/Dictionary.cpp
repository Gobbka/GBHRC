#include "Dictionary.h"
#include "../../BrokeProtocol.h"
#include "../../../../includes/logger.h"

using namespace Collections;

bool Enumerator::MoveNext()
{
	auto* mono_context = Mono::Context::get_context();
	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);

	if(this->version != this->dictionary->version)
	{
		DEBUG_LOG("U ARe A nigger");
		return false;
	}
	
	auto* method = mono_context->mono_class_get_method_from_name(
		klass,
		"MoveNext",
		-1
	);
	DEBUG_LOG("MOVE NEXT METHOD:" << method);

	Mono::MonoObject* exception;

	bool result = (bool)mono_context->mono_runtime_invoke(method, this, nullptr, &exception);
	if(exception!=nullptr)
	{
		mono_context->mono_print_system_exception(exception);
		return false;
	}
	return result;
}

int Dictionary::FindEntry(int key)
{
	auto* mono_context = Mono::Context::get_context();
	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);

	auto* method = mono_context->mono_class_get_method_from_name(
		klass,
		"FindEntry",
		-1
	);

	void* args[1]{ &key };
	return (int)mono_context->mono_runtime_invoke(method, this, args, nullptr);
}

void Dictionary::copy_to(Mono::MonoArray* array, int index)
{
	auto* mono_context = Mono::Context::get_context();
	void* args[1];
	args[0] = BrokeProtocol::GetLocalPlayer();

	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);

	DEBUG_LOG("KLASS: " << klass);
	if (klass == nullptr)
		return;
	
	auto* method = mono_context->mono_class_get_method_from_name(
		klass,
		"ContainsValue",
		-1
	);

	DEBUG_LOG("METHOD:"<<method);
	mono_context->mono_thread_attach(mono_context->mono_get_root_domain());
	Mono::MonoObject* exception;
	bool cont = (bool)mono_context->mono_runtime_invoke(
		method,
		this,
		args,
		&exception
	);
	if(exception!=nullptr)
	{
		DEBUG_LOG("NIGGER ERROR");
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
	auto* mono_context = Mono::Context::get_context();
	void* args[1]{ item };
	auto* method = mono_context->mono_class_get_method_from_name(
		mono_context->mono_object_get_class((Mono::MonoObject*)this),
		"ContainsValue",-1
	);
	return (bool)mono_context->mono_runtime_invoke(method, this, args, nullptr);
}

void Dictionary::clear()
{
	auto* mono_context = Mono::Context::get_context();
	// GetEnumerator
	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);

	auto* method = mono_context->mono_class_get_method_from_name(
		klass,
		"Clear",
		-1
	);

	mono_context->mono_runtime_invoke(method, this, nullptr, nullptr);
}

Enumerator* Dictionary::get_enumerator()
{
	auto* mono_context = Mono::Context::get_context();
	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);

	auto* method = mono_context->mono_class_get_method_from_name(
		klass,
		"GetEnumerator",
		-1
	);

	return (Enumerator*)mono_context->mono_runtime_invoke(method, this, nullptr, nullptr);
}
