#include "wndprochook.h"

WNDPROC prev_wndproc = 0;

Hooks::WndProc::tWndProcCallback t_callback = 0;
bool input_state = true;

IMPORT_LOGGER();

void Hooks::WndProc::init_hook(HWND hwnd)
{
	DEBUG_LOG("[WND] HWND: " << std::hex << std::uppercase << hwnd);

	SetLastError(0);
	prev_wndproc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)(WndProc::window_proc));
	if (prev_wndproc == 0)
	{
		DEBUG_LOG("[WND][-]: " << GetLastError());
	}
	else
		DEBUG_LOG("[WND] HOOKED: " << std::hex << std::uppercase << prev_wndproc);
}

LRESULT Hooks::WndProc::window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (t_callback)
		t_callback(uMsg, wParam, lParam);

	if (
		uMsg == WM_INPUT
		)
	{
		if (input_state == false)
			return 0;
	}

	return CallWindowProc(prev_wndproc, hWnd, uMsg, wParam, lParam);
}

void Hooks::WndProc::callback(tWndProcCallback callback)
{
	t_callback = callback;
}

void Hooks::WndProc::setInputState(bool state)
{
	input_state = state;
}
