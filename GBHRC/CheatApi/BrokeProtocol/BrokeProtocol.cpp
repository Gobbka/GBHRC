#include "BrokeProtocol.h"
#include "../../includes/win.h"
#include "../../includes/logger.h"

ClPlayer* BrokeProtocol::GetLocalPlayer()
{
	auto* const unity_player = GetModuleHandle(L"UnityPlayer.dll");
	auto ptr = *(size_t*)(*(size_t*)(*(size_t*)(*(size_t*)((size_t)unity_player + 0x19E0D60) + 0x80) + 0x3C8) + 0x108);
	return reinterpret_cast<ClPlayer*>(ptr);
}

void* BrokeProtocol::get_nigger()
{
	auto* const unity_player = GetModuleHandle(L"UnityPlayer.dll");
	auto ptr = *(size_t*)(*(size_t*)(*(size_t*)((size_t)unity_player + 0x19E0D60) + 0x80) + 0x3C8);
	return (void*)ptr;
}
