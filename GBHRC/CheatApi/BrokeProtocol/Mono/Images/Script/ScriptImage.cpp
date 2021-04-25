#include "ScriptImage.h"

#include "../../../../../includes/logger.h"

Mono::MonoMethod* Mono::ScriptImage::mono_get_method_from_name(const char* name, bool include_namespace)
{
    auto* mono_context = Mono::Context::get_context();
    auto* image = mono_context->get_script_image();
    auto* method_desc = mono_context->mono_method_desc_new(name, include_namespace);

    auto* pClass = mono_context->mono_class_from_name(image, method_desc->namespace_name, method_desc->class_name);
    auto* method = mono_context->mono_class_get_method_from_name(pClass, method_desc->method_name, -1);

    mono_context->mono_method_desc_free(method_desc);

    return method;
}
