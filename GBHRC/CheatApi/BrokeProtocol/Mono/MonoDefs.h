#pragma once
#include "../../../includes/win.h"

namespace Mono
{
	typedef struct MonoVTable MonoVTable;

	typedef struct _MonoClassField MonoClassField;
	typedef struct _MonoProperty MonoProperty;
	typedef struct _MonoEvent MonoEvent;
	typedef struct _MonoMethod MonoMethod;
	typedef struct _MonoImage MonoImage;
	typedef void MonoDomain;
	typedef void MonoDomain;
	typedef void MonoType;

	typedef struct {
		MonoVTable* vtable;
		void* synchronisation;
	} MonoObject;

	typedef struct
	{
		const char* namespace_name;
		const char* class_name;
		const char* method_name;
		const char* arguments;
		const char* unknown_data;
	} MonoMethodDesc;

	typedef struct {
		MonoObject* object;
		int length;
		unsigned char chars[0];
	} MonoString;

	typedef struct _MonoClass MonoClass;

	typedef enum {
		MONO_TYPE_NAME_FORMAT_IL,
		MONO_TYPE_NAME_FORMAT_REFLECTION,
		MONO_TYPE_NAME_FORMAT_FULL_NAME,
		MONO_TYPE_NAME_FORMAT_ASSEMBLY_QUALIFIED
	} MonoTypeNameFormat;

	typedef struct {
		UINT length;
		UINT lower_bound;
	} MonoArrayBounds;

	typedef struct {
		MonoObject obj;
		/* bounds is NULL for szarrays */
		MonoArrayBounds* bounds;
		/* total number of elements of the array */
		UINT max_length;
		/* we use double to ensure proper alignment on platforms that need it */
		__int64 vector[0];
	} MonoArray;
}
