#include <cstdio>

#include "includes/win.h"
#include "CheatApi/Hooks/d3d11/d3d11hook.h"
#include "Application/Form/Form.h"

#include "Forms/Menu/MenuMain.h"


Application::Form* menu;

void init_callback(Application::Render::Engine* instance)
{
    menu = new Application::Form();

    MainMenuMarkup(menu, instance);

    instance
        ->append_scene(menu);
}

void MainThread()
{
    HWND hwnd = Hooks::D3D11::FindMainWindow(GetCurrentProcessId());
#ifdef _DEBUG
    AllocConsole();
    auto nigger = freopen("CONOUT$", "w", stdout);
    nigger = freopen("CONIN$", "r", stdin);
#endif
    
    //WndProcHook::init_hook(hwnd);
    //WndProcHook::callback(wnd_key_hook);

    Hooks::D3D11::hook(Hooks::D3D11::GetPresentAddress(), init_callback);

    //WndProcHook::setInputState(false);
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, nullptr, 0, nullptr);
        break;

    case DLL_PROCESS_DETACH:
        FreeLibraryAndExitThread(hinstDLL, 0);
    }
    return TRUE;
}
