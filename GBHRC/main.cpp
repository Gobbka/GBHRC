#include <cstdio>

#include "includes/win.h"
#include "CheatApi/Hooks/d3d11/d3d11hook.h"
#include "CheatApi/Hooks/wndproc/wndprochook.h"
#include "Form/InteractiveForm.h"

#include "Forms/Menu/MenuMain.h"

#include "CheatApi/BrokeProtocol/Mono/Mono.h"
#include "CheatApi/BrokeProtocol/BrokeProtocol.h"

#include <string>
#include <sstream>

#include "UI/Panel/Panel.h"

HINSTANCE DllInst;
Application::InteractiveForm* menu;
Application::InteractiveForm* esp_scene;
Application::UI::Panel* esp_box;
void wnd_key_hook(UINT msg, WPARAM wParam, LPARAM lParam);
HWND main__window;


void draw_esp(Application::Render::Scene* pScene)
{
    if(BrokeProtocol::get_manager()->host != nullptr)
	{
        //system("cls");

        auto* local_player = BrokeProtocol::GetLocalPlayer();
        auto* local_position = local_player->rotationT->get_position();
        auto* local_matrix = BrokeProtocol::get_camera()->worldCamera->worldToCameraMatrix();
        if (local_matrix == nullptr)
            return;
    	
        auto* players = BrokeProtocol::GetPlayersCollection();
        auto* ptr = players->items->pointer();
        const auto size = players->items->size();
        //DEBUG_LOG("PLAYERS NEAR YOU:");

        {
            //auto* pos = UnityTypes::Vector3::make(0, 17.f, 0);

            //RECT rect;
            //GetClientRect(main__window, &rect);
            //auto w2s = WorldToScreen({ pos->x,pos->y,pos->z }, local_matrix,rect);
            //int width = rect.right - rect.left;
            //int height = rect.bottom - rect.top;
            //esp_box->set_pos(w2s.x - width/2,w2s.y + height/2);
            //DEBUG_LOG("X: " << w2s.x << " Y: " << w2s.y << " Z: "<<w2s.z);
        
        }

   		for(int i = 0;i<size;i++)
   		{
            auto* player = ptr[i];
   			
   			if(player == local_player)
                continue;

            auto* pos = player->rotationT->get_position();
   		}
   	}
}

void init_callback(Application::Render::Engine* instance)
{
    Mono::mono_thread_attach(Mono::mono_get_root_domain());

    menu = new Application::InteractiveForm();

    MainMenuMarkup(menu, instance);

    Application::register_form(menu);

    menu->hidden = true;

    esp_scene = new Application::InteractiveForm();
    esp_scene->render_callback = draw_esp;
    esp_scene->hidden = false;
    esp_box = new Application::UI::Panel{ {0,0},{30,30},{1,1,1} };
    esp_scene->add_markup_elements(1, esp_box);
    esp_scene->update_markup(instance);
	
    instance
        ->append_scene(menu)
		->append_scene(esp_scene);
	
}

void esp_();

void MainThread()
{
    main__window = Hooks::D3D11::FindMainWindow(GetCurrentProcessId());
	
    Application::set_main_hwnd(main__window);
#ifdef _DEBUG
    AllocConsole();
    auto nigger = freopen("CONOUT$", "w", stdout);
    nigger = freopen("CONIN$", "r", stdin);
#endif
	
    Hooks::WndProc::init_hook(main__window);
    Hooks::WndProc::callback(wnd_key_hook);

    Hooks::D3D11::hook(Hooks::D3D11::GetPresentAddress(), init_callback);
	
    Mono::mono_thread_attach(Mono::mono_get_root_domain());
    BrokeProtocol::show_local_message((char*)"<color=#39d668>[info]</color> GBHRC injected | press <color=#39d668>INSERT</color> to show menu!");
    BrokeProtocol::show_local_message((char*)"<color=#3966d6>[info]</color> join our discord: https://discord.gg/4jRzSHz3 ");

    esp_();
}

void esp_()
{
	//while(1)
	//{
	//	if(BrokeProtocol::get_manager()->host != nullptr)
	//	{
 //           auto* players = BrokeProtocol::GetPlayersCollection();
 //           auto* ptr = players->items->pointer();
 //           const auto size = players->items->size();
	//		for(int i = 0;i<size;i++)
	//		{
 //               auto* player = ptr[i];
 //               auto* pos = player->get_position();
 //               auto* angle = player->get_eulerAngles();
 //               DEBUG_LOG(std::dec<<player->ID<<": " << angle->x << " " <<angle->y << " " << angle->z);
	//		}
	//	}
 //       
 //       Sleep(5);
 //       system("cls");
	//}
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
            Mono::Dumper::dump_object((Mono::MonoObject*)BrokeProtocol::GetLocalPlayer()->rotationT->get_position());
            //BrokeProtocol::get_camera()->WorldCameraT->rotate(25.f,0,0);
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
