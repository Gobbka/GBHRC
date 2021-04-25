#pragma once
#include "vTable/vTable.h"
#include "../../../includes/win.h"
#include "dumper/MonoDumper.h"

namespace Mono
{
	class Context : public Mono::vTable
	{
	public:
		MonoMethod* mono_get_method_from_image(MonoImage* image, const char* desc, bool include_namespace = true, int param_count = -1);
		void	WINAPI mono_field_from_name_get_value(MonoObject* object, const char* name, void* pValue);
		void    WINAPI mono_get_static_field_value(MonoClass* klass, UINT token, void* value);

		
		void  WINAPI           mono_print_system_exception(void* exception);
		
		MonoObject*            create_csharp_string(char* ptr);
		MonoClass*             get_object_class();
		
		MonoImage*             get_script_image();
		MonoImage*             get_mscorlib();
		MonoImage*             get_UE_CoreModule();

		Context();

		static Mono::Context* get_context();
	};
}

//namespace Mono
//{
//	
//	void implement();
//

//
//}
