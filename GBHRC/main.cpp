#include <cstdio>

#include "includes/win.h"
#include "CheatApi/Hooks/d3d11/d3d11hook.h"
#include "CheatApi/Hooks/wndproc/wndprochook.h"
#include "Form/Form.h"

#include "Forms/Menu/MenuMain.h"

#include "CheatApi/BrokeProtocol/Mono/Mono.h"
#include "CheatApi/BrokeProtocol/BrokeProtocol.h"

#include <string>
#include <sstream>

HINSTANCE DllInst;
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
	
    Application::set_main_hwnd(hwnd);
#ifdef _DEBUG
    AllocConsole();
    auto nigger = freopen("CONOUT$", "w", stdout);
    nigger = freopen("CONIN$", "r", stdin);
#endif
	
    Hooks::WndProc::init_hook(hwnd);
    Hooks::WndProc::callback(wnd_key_hook);

    Mono::mono_thread_attach(Mono::mono_get_root_domain());
    BrokeProtocol::show_local_message((char*)"<color=#39d668>[info]</color> GBHRC injected | press <color=#39d668>INSERT</color> to show menu!");
    BrokeProtocol::show_local_message((char*)"<color=#3966d6>[info]</color> join our discord: https://discord.gg/4jRzSHz3 ");

    DEBUG_LOG("ENTER POINTER OF SHIT TO DUMP");

	while(1)
	{
        __int64 gobka=0;
        std::cin >> gobka;
        DEBUG_LOG("ENTERED: " << gobka);
		if(gobka ==0)
            continue;
        Mono::mono_thread_attach(Mono::mono_get_root_domain());
        Mono::mono_dump_class(
            Mono::mono_object_get_class(
            (Mono::MonoObject*)gobka)
        );
	}
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
            BrokeProtocol::GetLocalPlayer()->jump();
        }

        if(wParam == VK_F4)
        {
            BrokeProtocol::GetLocalPlayer()->clear_injuries();
        }

    	if(wParam == VK_F2){

            auto* ptr = BrokeProtocol::GetPlayersCollection()->items;
            auto* player_pointer = ptr->pointer();
    		
            BrokeProtocol::GetLocalPlayer()->rotationT->rotate(0, 25.f, 0);
    	}

        if (wParam == VK_F3)
        {
            BrokeProtocol::GetLocalPlayer()->fire();
        }
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
        DllInst = hinstDLL;
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, nullptr, 0, nullptr);
        break;

    case DLL_PROCESS_DETACH:
        FreeLibraryAndExitThread(hinstDLL, 0);
    }
    return TRUE;
}
