#include <cstdio>

#include "includes/win.h"
#include "CheatApi/Hooks/d3d11/d3d11hook.h"
#include "CheatApi/Hooks/wndproc/wndprochook.h"
#include "Application/Form/Form.h"

#include "Forms/Menu/MenuMain.h"


Application::Form* menu;
void wnd_key_hook(UINT msg, WPARAM wParam, LPARAM lParam);

void init_callback(Application::Render::Engine* instance)
{
    menu = new Application::Form();

    MainMenuMarkup(menu, instance);

    instance
        ->append_scene(menu);

    Application::register_form(menu);
}

void MainThread()
{
    HWND hwnd = Hooks::D3D11::FindMainWindow(GetCurrentProcessId());
#ifdef _DEBUG
    AllocConsole();
    auto nigger = freopen("CONOUT$", "w", stdout);
    nigger = freopen("CONIN$", "r", stdin);
#endif

    Hooks::WndProc::init_hook(hwnd);
    Hooks::WndProc::callback(wnd_key_hook);

    Hooks::D3D11::hook(Hooks::D3D11::GetPresentAddress(), init_callback);

    //WndProcHook::setInputState(false);
}

void wnd_key_hook(UINT msg, WPARAM wParam, LPARAM lParam)
{
    Application::wnd_proc(msg, wParam, lParam);

    if (msg == WM_KEYUP)
    {
        if (wParam == VK_DELETE)
        {

        }

        if (wParam == VK_INSERT)
        {
            static bool interactive_state = true;

            menu->hidden = interactive_state;
            Hooks::WndProc::setInputState(interactive_state);

            interactive_state = !interactive_state;
        }

        if (wParam == VK_F5)
        {
            //DEBUG_LOG("[GBP] INITING");
            //local_player = BPMemory::GetLocalPlayer();
            //local_player->WeightLimit = 5000.f;
            //ENetHook::hook();
        }

        if (wParam == VK_RIGHT)
        {
            //UIDrawer::instance()->menu_layer->move_inner_by(5.f, 0.f);
            //local_player->StartSpeed += 5.f;
            //DEBUG_LOG("[GBP] SPEED: " << local_player->StartSpeed);
        }

        if (wParam == VK_LEFT)
        {
            //UIDrawer::instance()->menu_layer->move_inner_by(-5.f, 0.f);
            //local_player->StartSpeed -= 5.f;
            //DEBUG_LOG("[GBP] SPEED: " << local_player->StartSpeed);
        }
    }
    else
    {

    }

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
