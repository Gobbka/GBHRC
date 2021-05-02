#pragma once
#include "../../../includes/logger.h"
#include "../../../includes/win.h"

namespace Hooks
{
	namespace WndProc
	{
		void init_hook(HWND hwnd);
		LRESULT window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		typedef void(*tWndProcCallback)(UINT msg, WPARAM wParam, LPARAM lParam);
		void callback(tWndProcCallback callback);
		void setInputState(bool state);
	}
}
