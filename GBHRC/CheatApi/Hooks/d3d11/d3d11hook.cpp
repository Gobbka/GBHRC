#include "d3d11hook.h"
#include "../../../includes/logger.h"
#include "D3D11_VMT.h"

struct HandleData
{
	DWORD pid;
	HWND hWnd;
};

Application::Render::Engine* pRenderEngine = nullptr;
Hooks::D3D11::fnInitCallback hook_init_callback;
//
Hooks::D3D11::fnPresent Original_Present_Func = nullptr;
char original_present_func_bytes[5];
//

void place_catch_bytes(size_t address)
{
	*(char*)(address) = (char)0xE9;
	*(unsigned int*)(address + (DWORD)1) = (size_t)Hooks::D3D11::HookedPresentFunction - (size_t)address - 5;
}

Hooks::D3D11::fnPresent Hooks::D3D11::GetPresentAddress()
{
	if (Original_Present_Func != nullptr)
	{
		return Original_Present_Func;
	}
	// make dummy device
	D3D_FEATURE_LEVEL ft_level;
	DXGI_SWAP_CHAIN_DESC sd{ 0 };
	sd.BufferCount = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.Height = 800;
	sd.BufferDesc.Width = 600;
	sd.BufferDesc.RefreshRate = { 60,1 };
	sd.OutputWindow = GetForegroundWindow();
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.SampleDesc = { 1,0 };

	ID3D11Device* pDevice;
	IDXGISwapChain* pSwapChain;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_REFERENCE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		&ft_level,
		nullptr
	);

	if (FAILED(hr))
		return 0;

	void** pVMT = *(void***)pSwapChain;
	const auto present = (fnPresent)pVMT[(UINT)IDXGISwapChainVMT::Present];

	safe_release(pSwapChain);
	safe_release(pDevice);

	Original_Present_Func = present;

	return present;
}

void Hooks::D3D11::hook(fnPresent present_func, fnInitCallback init_callback)
{
	DEBUG_LOG("[D3D] PRESENT ADDRESS: " << std::hex << std::uppercase << (size_t)present_func);
	DEBUG_LOG("[D3D] HOOK ADDRESS: " << Hooks::D3D11::HookedPresentFunction);
	DEBUG_LOG("[D3D] ORIGINAL BYTES: " << &original_present_func_bytes);

	DWORD oldProt;

	VirtualProtect(original_present_func_bytes, 5, PAGE_READWRITE, &oldProt);

	if (!VirtualProtect((LPVOID)present_func, 10, PAGE_EXECUTE_READWRITE, &oldProt))
	{
		DEBUG_LOG("[D3D][-] THIS HORNY NIGGER DONT WANNA GIVE ACCESS. ERROR CODE: " << GetLastError());
		return;
	}

	DEBUG_LOG("[D3D] COPY ORIGINAL BYTES");
	memcpy(original_present_func_bytes, (char*)present_func, 5);

	hook_init_callback = init_callback;

	DEBUG_LOG("[D3D] REPLACING BYTES");
	place_catch_bytes((size_t)present_func);
	DEBUG_LOG("[D3D] PLACED");
}

void Hooks::D3D11::HookedPresentFunction(IDXGISwapChain* self, UINT SyncInterval, UINT Flags)
{
	// if this function called first time
	// we make instance of own graphic engine
	if (pRenderEngine == nullptr)
	{
		DEBUG_LOG("[d3d] CATCHED");
		//
		DXGI_SWAP_CHAIN_DESC sd;
		self->GetDesc(&sd);
		HWND window = sd.OutputWindow;

		ID3D11Device* pDevice;
		HRESULT hr = self->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice);

		if (FAILED(hr))
			DEBUG_LOG("[d3d][-] CANNOT GET DEVICE");


		pRenderEngine = new Application::Render::Engine(window, pDevice, self);
		hook_init_callback(pRenderEngine);
	}

	pRenderEngine->update_scene();
	pRenderEngine->present();

	// then we need to back original bytes
	auto present_func = GetPresentAddress();
	memcpy(present_func, original_present_func_bytes, 5);
	present_func(self, SyncInterval, Flags);

	place_catch_bytes((size_t)present_func);
}

BOOL CALLBACK EnumWindowsCallback(HWND hWnd, LPARAM lParam)
{
	HandleData& data = *(HandleData*)lParam;
	DWORD pid = 0;
	GetWindowThreadProcessId(hWnd, &pid);
	if (pid == data.pid && GetWindow(hWnd, GW_OWNER) == HWND(0) && IsWindowVisible(hWnd))
	{
		data.hWnd = hWnd;
		return FALSE;
	}

	return TRUE;
}

HWND Hooks::D3D11::FindMainWindow(DWORD dwPID)
{
	HandleData handleData{ 0 };
	handleData.pid = dwPID;
	EnumWindows(EnumWindowsCallback, (LPARAM)&handleData);
	return handleData.hWnd;
}
