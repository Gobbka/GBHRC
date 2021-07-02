#include "Dictionary.h"
#include "../../BrokeProtocol.h"
#include "../../../../includes/logger.h"

using namespace Collections;

bool Enumerator::MoveNext()
{
	auto* mono_context = Mono::Context::get_context();
	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);
	
	auto* method = mono_context->mono_class_get_method_from_name(
		klass,
		"MoveNext",
		-1
	);
	DEBUG_LOG("MOVE NEXT METHOD:" << method);

	Mono::MonoObject* exception;
	
	auto result = (MonoBool*)mono_context->mono_runtime_invoke(method, this, nullptr, &exception);

	if(exception != nullptr)
	{
		mono_context->mono_print_system_exception(exception);

		DEBUG_LOG(this->version << " " << this->dictionary->version);
		
		return false;
	}

	return result->value;
}

void Enumerator::reset()
{
	auto* mono_context = Mono::Context::get_context();
	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);
	DEBUG_LOG(mono_context->mono_class_get_name(klass));
	auto* method = mono_context->mono_class_get_method_from_name(
		klass,
		"Reset",
		-1
	);
	DEBUG_LOG(mono_context->mono_class_get_name(klass));
	DEBUG_LOG("RESET METHOD:" << method);
	if (method == nullptr)
		return;

	Mono::MonoObject* exception;

	mono_context->mono_runtime_invoke(method, this, nullptr, &exception);

	if (exception != nullptr)
	{
		Mono::Dumper::dump_object(exception);
		mono_context->mono_print_system_exception(exception);
	}
}

void* Enumerator::current()
{
	auto* mono_context = Mono::Context::get_context();
	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);

	static auto* get_method = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		klass,
		"Current"
	));

	DEBUG_LOG("CURRENT METHOD: " << get_method);

	return (void*)mono_context->mono_runtime_invoke(get_method, this, nullptr, nullptr);
}

Entry* Enumerator::entry()
{
	auto* mono_context = Mono::Context::get_context();
	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);
	
	static auto* get_method = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		klass,
		"position"
	));

	DEBUG_LOG("NIGGER: "<<get_method);

	return (Entry*)mono_context->mono_runtime_invoke(get_method, this, nullptr, nullptr);
}

Enumerator* ValueCollection::get_enumerator()
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

Mono::MonoArray* ValueCollection::to_array()
{
	// ToArray
	auto* mono_context = Mono::Context::get_context();
	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);

	auto* method = mono_context->mono_class_get_method_from_name(
		klass,
		"ToArray",
		-1
	);


	DEBUG_LOG(method);


	if (method == nullptr)
		return nullptr;


	return (Mono::MonoArray*)mono_context->mono_runtime_invoke(method, this, nullptr, nullptr);
}

void ValueCollection::copy_to(Mono::MonoArray* array, int index)
{
	auto* mono_context = Mono::Context::get_context();
	void* args[]{ array,&index };

	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);

	auto* method = mono_context->mono_class_get_method_from_name(
		klass,
		"CopyTo",
		-1
	);

	Mono::MonoObject* exception;

	mono_context->mono_runtime_invoke(
		method,
		this,
		args,
		&exception
	);

	if (exception != nullptr)
		DEBUG_LOG("NIGGER ERROR");
}

int ValueCollection::count()
{
	auto* mono_context = Mono::Context::get_context();
	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);

	static auto* get_method = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		klass,
		"Count"
	));

	return ((MonoInt*)mono_context->mono_runtime_invoke(get_method, this, nullptr, nullptr))->value;
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
	return ((MonoInt*)mono_context->mono_runtime_invoke(method, this, args, nullptr))->value;
}

void Dictionary::copy_to(Mono::MonoArray* array, int index)
{
	auto* mono_context = Mono::Context::get_context();
	void* args[] {array,&index};

	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);
	
	auto* method = mono_context->mono_class_get_method_from_name(
		klass,
		"CopyTo",
		-1
	);

	Mono::MonoObject* exception;
	
	mono_context->mono_runtime_invoke(
		method,
		this,
		args,
		&exception
	);
	
	if(exception!=nullptr)
		DEBUG_LOG("NIGGER ERROR");
}

bool Dictionary::contains(void* item)
{
	auto* mono_context = Mono::Context::get_context();
	void* args[1]{ item };
	auto* method = mono_context->mono_class_get_method_from_name(
		mono_context->mono_object_get_class((Mono::MonoObject*)this),
		"ContainsValue",-1
	);
	return ((MonoBool*)mono_context->mono_runtime_invoke(method, this, args, nullptr))->value;
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

ValueCollection* Dictionary::get_values()
{
	auto* mono_context = Mono::Context::get_context();
	auto* klass = mono_context->mono_object_get_class((Mono::MonoObject*)this);

	static auto* get_method = mono_context->mono_property_get_get_method(mono_context->mono_class_get_property_from_name(
		klass,
		"Values"
	));

	return (ValueCollection*)mono_context->mono_runtime_invoke(get_method, this, nullptr, nullptr);
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
