#include <cstdio>

#include "includes/win.h"
#include "CheatApi/Hooks/d3d11/d3d11hook.h"
#include "CheatApi/Hooks/wndproc/wndprochook.h"

#include "Form/Interactive/InteractiveForm.h"
#include "Form/Canvas/CanvasForm.h"
#include "Form/Canvas/elements/rectangle/rectangle.h"

#include "Forms/Menu/MenuMain.h"

#include "CheatApi/BrokeProtocol/Mono/Mono.h"
#include "CheatApi/BrokeProtocol/BrokeProtocol.h"

#include "CheatApi/GBHRC/gbhrc.h"

#include <string>
#include <sstream>

HINSTANCE DllInst;
Application::InteractiveForm* menu;
Application::Canvas::CanvasForm* esp_scene;
void wnd_key_hook(UINT msg, WPARAM wParam, LPARAM lParam);
HWND main__window;
Mono::Context* mono_context;

void init_callback(Application::Render::Engine* instance)
{
    mono_context->mono_thread_attach(mono_context->mono_get_root_domain());

    BrokeProtocol::show_local_message((char*)"<color=#39d668>[info]</color> GBHRC injected | press <color=#39d668>INSERT</color> to show menu!");
	BrokeProtocol::show_local_message((char*)"<color=#3966d6>[info]</color> join our discord: https://discord.gg/4jRzSHz3 ");
	
    menu = new Application::InteractiveForm();

    MainMenuMarkup(menu, instance);
	
    Application::register_form(menu);
    
    menu->hidden = true;

    esp_scene = new Application::Canvas::CanvasForm();
    esp_scene->render_callback = GBHRC::Context::static_draw_callback;
    esp_scene->hidden = false;
	
	for(int i = 0;i<100;i++)
	{
        auto* element = new Application::Canvas::Rectangle{ {0,0},{30,30},{0,0.8,0} };
        element->render = false;
        esp_scene->add_element(element);
	}

    esp_scene->update_markup(instance);
	
    instance
        ->append_scene(menu);
		//->append_scene(esp_scene);
}

void MainThread()
{
    main__window = Hooks::D3D11::FindMainWindow(GetCurrentProcessId());
    Hooks::D3D11::fnPresent present_addres;
	auto hr = Hooks::D3D11::GetPresentAddress(&present_addres);
	
    Application::implement(main__window);

    AllocConsole();
    auto nigger = freopen("CONOUT$", "w", stdout);
    nigger = freopen("CONIN$", "r", stdin);

	if(FAILED(hr))
	{
        DEBUG_LOG("CANNOT GET PRESENT ADDRESS: "<<std::hex<<hr);
        return;
	}
	
    Hooks::WndProc::init_hook(main__window);
    Hooks::WndProc::callback(wnd_key_hook);

    mono_context = Mono::Context::get_context();
    mono_context->mono_thread_attach(mono_context->mono_get_root_domain());
	
    Hooks::D3D11::hook(present_addres, init_callback);

    GBHRC::Context::instance()->life_cycle();
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
            bool state = menu->hidden;

            menu->hidden = !state;
            Hooks::WndProc::setInputState(!state);
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
            Mono::Dumper::dump_object((Mono::MonoObject*)BrokeProtocol::GetLocalPlayer()->stance);
    	}

    	if(wParam == VK_LEFT)
    	{
            BrokeProtocol::GetLocalPlayer()->speed -= 2.f;
            DEBUG_LOG("SPEED: "<<BrokeProtocol::GetLocalPlayer()->speed);
    	}
    	if(wParam == VK_RIGHT)
    	{
            BrokeProtocol::GetLocalPlayer()->speed += 2.f;
            DEBUG_LOG("SPEED: " << BrokeProtocol::GetLocalPlayer()->speed);
    	}
    }


	if(msg == WM_LBUTTONDOWN)
	{
        GBHRC::Context::instance()->aim_active = true;
	}
	if(msg == WM_LBUTTONUP)
	{
        GBHRC::Context::instance()->aim_active = false;
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
