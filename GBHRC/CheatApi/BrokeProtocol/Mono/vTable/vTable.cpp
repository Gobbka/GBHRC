#include "vTable.h"

HMODULE Mono::vTable::getModule()
{
	static HMODULE hModule = hModule = GetModuleHandle(L"mono-2.0-bdwgc.dll");

	return hModule;
}

void Mono::vTable::implement()
{
	auto* module = getModule();
	this->mono_array_new = (MonoArray * (WINAPI*)(MonoDomain*, MonoClass*, uintptr_t))GetProcAddress(module, "mono_array_new");
	this->mono_object_new = (MonoObject * (WINAPI*)(MonoDomain*, MonoClass*))GetProcAddress(module, "mono_object_new");
	this->mono_image_loaded = (MonoImage * (WINAPI*)(const char*))GetProcAddress(module, "mono_image_loaded");
	this->mono_get_root_domain = (MonoDomain * (WINAPI*)())GetProcAddress(module, "mono_get_root_domain");
	this->mono_method_desc_new = (MonoMethodDesc * (WINAPI*)(const char*, bool))GetProcAddress(module, "mono_method_desc_new");
	this->mono_method_desc_free = (void(WINAPI*)(MonoMethodDesc*))GetProcAddress(module, "mono_method_desc_free");
	this->mono_method_desc_search_in_class = (MonoMethod * (WINAPI*)(MonoMethodDesc*, MonoClass*))GetProcAddress(module, "mono_method_desc_search_in_class");
	this->mono_object_get_virtual_method = (MonoMethod * (WINAPI*)(MonoObject*, MonoMethod*))GetProcAddress(module, "mono_object_get_virtual_method");
	this->mono_class_get_method_from_name = (MonoMethod * (WINAPI*)(MonoClass*, const char*, int))GetProcAddress(module, "mono_class_get_method_from_name");
	this->mono_property_get_get_method = (MonoMethod * (WINAPI*)(MonoProperty*))GetProcAddress(module, "mono_property_get_get_method");
	this->mono_property_get_set_method = (MonoMethod * (WINAPI*)(MonoProperty*))GetProcAddress(module, "mono_property_get_set_method");
	this->mono_class_get_name = (const char* (WINAPI*)(MonoClass*))GetProcAddress(module, "mono_class_get_name");
	this->mono_method_get_token = (UINT(WINAPI*)(MonoMethod*))GetProcAddress(module, "mono_method_get_token");
	this->mono_method_get_name = (const char* (WINAPI*)(MonoMethod*))GetProcAddress(module, "mono_method_get_name");
	this->mono_class_vtable = (MonoVTable * (WINAPI*)(MonoDomain*, MonoClass*))GetProcAddress(module, "mono_class_vtable");
	this->mono_field_static_get_value = (void(WINAPI*)(MonoVTable*, MonoClassField*, void*))GetProcAddress(module, "mono_field_static_get_value");
	this->mono_class_from_name = (MonoClass * (WINAPI*)(MonoImage*, const char*, const char*))GetProcAddress(module, "mono_class_from_name");
	this->mono_object_get_class = (MonoClass * (WINAPI*)(MonoObject*))GetProcAddress(module, "mono_object_get_class");
	this->mono_class_get_parent = (MonoClass * (WINAPI*)(MonoClass*))GetProcAddress(module, "mono_class_get_parent");
	this->mono_class_get_field = (MonoClassField * (WINAPI*)(MonoClass*, UINT))GetProcAddress(module, "mono_class_get_field");
	this->mono_field_from_token = (MonoClassField * (WINAPI*)(UINT))GetProcAddress(module, "mono_field_from_token");
	this->mono_class_get_field_from_name = (MonoClassField * (WINAPI*)(MonoClass*, const char*))GetProcAddress(module, "mono_class_get_field_from_name");
	this->mono_field_get_name = (const char* (WINAPI*)(MonoClassField*))GetProcAddress(module, "mono_field_get_name");
	this->mono_field_get_value = (void (WINAPI*)(MonoObject*, MonoClassField*, void*))GetProcAddress(module, "mono_field_get_value");
	this->mono_field_get_offset = (UINT(WINAPI*)(MonoClassField*))GetProcAddress(module, "mono_field_get_offset");
	this->mono_class_get_field_token = (UINT(WINAPI*)(MonoClassField*))GetProcAddress(module, "mono_class_get_field_token");
	this->mono_class_get_property_from_name = (MonoProperty * (WINAPI*)(MonoClass*, const char*))GetProcAddress(module, "mono_class_get_property_from_name");
	this->mono_class_get_fields = (MonoClassField * (WINAPI*)(MonoClass*, void*))GetProcAddress(module, "mono_class_get_fields");
	this->mono_class_get_methods = (MonoMethod * (WINAPI*)(MonoClass*, void*))GetProcAddress(module, "mono_class_get_methods");
	this->mono_thread_attach = (void(WINAPI*)(MonoDomain*))GetProcAddress(module, "mono_thread_attach");
	this->mono_runtime_invoke = (void* (WINAPI*)(MonoMethod*, void*, void**, MonoObject**))GetProcAddress(module, "mono_runtime_invoke");
	this->mono_image_get_filename = (const char*(WINAPI*)(MonoImage*))GetProcAddress(module, "mono_image_get_filename");
	this->mono_image_get_name = (const char*(WINAPI*)(MonoImage*))GetProcAddress(module, "mono_image_get_name");
	this->mono_object_get_size = (UINT(WINAPI*)(MonoObject*))GetProcAddress(module, "mono_object_get_size");
	this->mono_class_instance_size = (UINT(WINAPI*)(MonoClass*))GetProcAddress(module, "mono_class_instance_size");
}
