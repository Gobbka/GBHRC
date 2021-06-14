#pragma once
#define DllExport __declspec(dllexport)
#define GBHRCAPI __stdcall
#include <Windows.h>

extern "C"{
	DllExport BOOL GBHRCAPI inject();
	DllExport BOOL GBHRCAPI SendLuaScript(char*script);
	DllExport BOOL GBHRCAPI AttachToProcess();
	DllExport BOOL GBHRCAPI DeAttachFromProcess();
}
