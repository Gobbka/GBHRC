#include "Detour.h"

void Detouring::DetourContext::callback_void(UINT index)
{
	
}

void Detouring::DetourContext::implement()
{
	DetourContext::index = 0;
}

void Detouring::DetourContext::register_detour(Detour* LPDetour, DWORD address, DWORD to)
{
	VirtualProtect(LPDetour, sizeof(Detour), PAGE_EXECUTE_READWRITE, nullptr);
	// PUSH INDEX TO STACK
	LPDetour->bytes[0] = (char)0XA6;
	memcpy(&LPDetour->bytes[1], &DetourContext::index, sizeof(index));
	// CALL OUR FUNC
	
	// POP INDEX FROM STACK

	// JUMP BACK


	DetourContext::index++;
}
