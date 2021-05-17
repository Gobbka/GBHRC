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

#include "CheatApi/BrokeProtocol/classes/Guns/ShBallistic.h"
#include "includes/clientdefs.h"

#include "Asserts/VersionAssert/ClientVersionAssers.h"
#include "Forms/FriendList/FriendList.h"


// static_assert(offsetof(BrokeProtocol::ShBallistic, recoil) == 0X01E4,"WRONG OFFSET");

HINSTANCE DllInst;
Application::InteractiveForm* menu;
Application::InteractiveForm* friend_list;
Application::Canvas::CanvasForm* esp_scene;
void wnd_key_hook(UINT msg, WPARAM wParam, LPARAM lParam);
HWND main__window;
extern Mono::Context* MonoContext;

void init_callback(Application::Render::Engine* instance)
{
    DEBUG_LOG("INIT CALLBACK");
    MonoContext->mono_thread_attach(MonoContext->mono_get_root_domain());

    BrokeProtocol::show_local_message((char*)"<color=#39d668>[info]</color> GBHRC injected | press <color=#39d668>INSERT</color> to show menu!");
	BrokeProtocol::show_local_message((char*)"<color=#3966d6>[info]</color> join our discord: " DISCORD_CHANNEL);

    DEBUG_LOG("USER WELCOMED");
	
    menu = new Application::InteractiveForm();
    friend_list = new Application::InteractiveForm();
	
    Application::register_form(menu);
    Application::register_form(friend_list);

    MainMenuMarkup(menu, instance);
    FiendListMarkup(friend_list, instance);
    
    menu->hidden = true;
    friend_list->hidden = true;

    DEBUG_LOG("MENU FORM REGISTERED");
	
    esp_scene = new Application::Canvas::CanvasForm();
    esp_scene->render_callback = GBHRC::Context::static_draw_callback;
    esp_scene->hidden = false;
    GBHRC::Context::instance()->set_esp_scene(esp_scene);
    GBHRC::Context::instance()->make_esp_boxes();

    DEBUG_LOG("ESP REGISTERED");
	
    instance
        ->append_scene(menu)
        ->append_scene(friend_list)
	
		->append_scene(esp_scene)	
	;

    DEBUG_LOG("SCENE'S APPENDED");

    esp_scene->update_markup(instance);
}


void MainThread()
{
	
    main__window = Hooks::D3D11::FindMainWindow(GetCurrentProcessId());
	
#ifdef DEBUG
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
#endif

    {
        MonoContext = Mono::Context::get_context();

        MonoContext->mono_thread_attach(MonoContext->mono_get_root_domain());
        DEBUG_LOG("CHECKING VERSION...");
        if(ClientVersionAsserts::check_bp_version()==false)
        {
        	// abort without refs to exit()
            MonoContext->mono_runtime_invoke(nullptr, nullptr, nullptr, nullptr);
            return;
        }
    }
    DEBUG_LOG("INSTALLED LAST VERSION");
    {
        Hooks::WndProc::init_hook(main__window);
        Hooks::WndProc::callback(wnd_key_hook);
    }
	
    Hooks::D3D11::fnPresent present_addres;
    auto hr = Hooks::D3D11::GetPresentAddress(&present_addres);

    Application::implement(main__window);

    if (FAILED(hr))
    {
        DEBUG_LOG("CANNOT GET PRESENT ADDRESS: " << std::hex << hr);
        return;
    }
	
    Hooks::D3D11::hook(present_addres, init_callback);
	
    {
        auto context = GBHRC::Context::instance();
        context->implement(DllInst);
        context->life_cycle();
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
            bool state = menu->hidden;

            menu->hidden = !state;
            friend_list->hidden = !state;
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
            auto playrator = BrokeProtocol::GetPlayersCollection()->items->iterator();
    		while(playrator.next())
    		{
                auto* item = playrator.item();
                DEBUG_LOG("ID: " << item->ID << " " << item->health);
    		}
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
