#pragma once
#define DllExport __declspec(dllexport)
#define GBHRCAPI __stdcall

extern "C"{
	DllExport void GBHRCAPI inject();
}
