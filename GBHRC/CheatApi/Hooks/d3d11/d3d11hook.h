#pragma once
#include "../../../includes/d3d.h"
#include "Application.h"
#include "Render/Engine/Engine.h"

namespace Hooks
{
	namespace D3D11
	{
		typedef HRESULT(__stdcall* fnPresent)(IDXGISwapChain* self, UINT SyncInterval, UINT Flags);
		typedef void(*fnInitCallback)(Application::Render::Engine* instance);

		HRESULT GetPresentAddress(fnPresent*outPresent);
		void hook(fnPresent present_func, fnInitCallback init_callback);
		void HookedPresentFunction(IDXGISwapChain* self, UINT SyncInterval, UINT Flags);

		HWND FindMainWindow(DWORD dwPID);
	}
}
