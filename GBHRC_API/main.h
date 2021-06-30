#pragma once
#define DllExport __declspec(dllexport)
#define GBHRCAPI __cdecl
#include <Windows.h>


extern "C"{
	
	typedef struct 
	{
		BOOL status;
		const char* response;
	} GBHRCAPI_RESPONSE;

	
	DllExport GBHRCAPI_RESPONSE GBHRCAPI Inject();
	DllExport GBHRCAPI_RESPONSE GBHRCAPI SendLuaScript(char*script);
	DllExport GBHRCAPI_RESPONSE GBHRCAPI AttachToProcess();
	DllExport GBHRCAPI_RESPONSE GBHRCAPI DeAttachFromProcess();
}
