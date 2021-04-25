#include "ICollection.h"

#include "../../../../includes/logger.h"

ICollection::ICollection(Mono::MonoObject* pCollection)
{
	this->collection = pCollection;
}

int ICollection::Count() const
{
	auto* mono_context = Mono::Context::get_context();
	auto* klass = mono_context->mono_object_get_class(this->collection);
	auto* pProperty = mono_context->mono_class_get_property_from_name(klass, "Count");

	auto* pMethod = mono_context->mono_property_get_get_method(pProperty);

	return (int)mono_context->mono_runtime_invoke(pMethod, this->collection, nullptr, nullptr);
}
