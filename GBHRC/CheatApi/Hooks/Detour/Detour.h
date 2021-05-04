#pragma once
#include <Windows.h>
#include <vector>

namespace Detouring
{
	struct Detour
	{
	public:
		char bytes[20];
		
	};
	
	class DetourContext
	{
	private:
		static std::vector<int> registered_procedures;
		static UINT index;
		static void __cdecl callback_void(UINT index);
	public:
		static void implement();
		static void register_detour(Detour* LPDetour, DWORD address, DWORD to);
	};
	
}
