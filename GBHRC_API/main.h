#pragma once
#define DllExport __declspec(dllexport)
#define GBHRCAPI __stdcall
#include <Windows.h>


extern "C"{
	struct GBHRCAPI_RESPONSE
	{
		BOOL status;
		const char* response;

		GBHRCAPI_RESPONSE(BOOL status, const char* response)
		{
			this->status = status;
			this->response = response;
		}
	};

	
	DllExport GBHRCAPI_RESPONSE GBHRCAPI Inject();
	DllExport GBHRCAPI_RESPONSE GBHRCAPI SendLuaScript(char*script);
	DllExport GBHRCAPI_RESPONSE GBHRCAPI AttachToProcess();
	DllExport GBHRCAPI_RESPONSE GBHRCAPI DeAttachFromProcess();
}
