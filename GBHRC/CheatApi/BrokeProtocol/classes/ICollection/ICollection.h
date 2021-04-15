#pragma once
#include "../../Mono/Mono.h"

class ICollection
{
	Mono::MonoObject* collection;
public:
	ICollection(Mono::MonoObject*pCollection);
	int Count() const;
};

