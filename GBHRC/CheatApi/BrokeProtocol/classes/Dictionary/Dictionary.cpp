#include "Dictionary.h"
#include "../../BrokeProtocol.h"
#include "../../../../includes/logger.h"

bool Enumerator::MoveNext()
{
	auto* klass = Mono::mono_object_get_class((Mono::MonoObject*)this);

	if(this->version != this->dictionary->version)
	{
		DEBUG_LOG("U ARe A nigger");
		return false;
	}
	
	auto* method = Mono::mono_class_get_method_from_name(
		klass,
		"MoveNext",
		-1
	);
	DEBUG_LOG("MOVE NEXT METHOD:" << method);

	Mono::MonoObject* exception;

	bool result = (bool)Mono::mono_runtime_invoke(method, this, nullptr, &exception);
	if(exception!=nullptr)
	{
		Mono::mono_print_system_exception(exception);
		return false;
	}
	return result;
}

int Dictionary::FindEntry(int key)
{
	auto* klass = Mono::mono_object_get_class((Mono::MonoObject*)this);

	auto* method = Mono::mono_class_get_method_from_name(
		klass,
		"FindEntry",
		-1
	);

	void* args[1]{ &key };
	return (int)Mono::mono_runtime_invoke(method, this, args, nullptr);
}

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

void Dictionary::clear()
{
	// GetEnumerator
	auto* klass = Mono::mono_object_get_class((Mono::MonoObject*)this);

	auto* method = Mono::mono_class_get_method_from_name(
		klass,
		"Clear",
		-1
	);

	Mono::mono_runtime_invoke(method, this, nullptr, nullptr);
}

Enumerator* Dictionary::get_enumerator()
{
	// GetEnumerator
	auto* klass = Mono::mono_object_get_class((Mono::MonoObject*)this);

	auto* method = Mono::mono_class_get_method_from_name(
		klass,
		"GetEnumerator",
		-1
	);

	return (Enumerator*)Mono::mono_runtime_invoke(method, this, nullptr, nullptr);
}
