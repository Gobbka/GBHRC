#include "ICollection.h"

#include "../../../../includes/logger.h"

ICollection::ICollection(Mono::MonoObject* pCollection)
{
	this->collection = pCollection;
}

int ICollection::Count() const
{
	auto* klass = Mono::mono_object_get_class(this->collection);
	auto* pProperty = Mono::mono_class_get_property_from_name(klass, "Count");
	DEBUG_LOG("PROPERTY: "<<pProperty);
	auto* pMethod = Mono::mono_property_get_get_method(pProperty);
	DEBUG_LOG("METHOD: " << pMethod);
	return (int)Mono::mono_runtime_invoke(pMethod, this->collection, nullptr, nullptr);
}
