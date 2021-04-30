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

#include <string>
#include <sstream>

HINSTANCE DllInst;
Application::InteractiveForm* menu;
Application::Canvas::CanvasForm* esp_scene;
Application::Canvas::Rectangle* esp_box;
void wnd_key_hook(UINT msg, WPARAM wParam, LPARAM lParam);
HWND main__window;
Mono::Context* mono_context;

void draw_esp(Application::Render::Scene* pScene)
{
    if(BrokeProtocol::get_manager()->host != nullptr)
	{
        system("cls");

        auto* local_player = BrokeProtocol::GetLocalPlayer();
        auto* local_position = local_player->rotationT->get_position();
    	
        auto* local_matrix = BrokeProtocol::get_camera()->worldCamera->worldToCameraMatrix();
        if (local_matrix == nullptr)
            return;
        auto* players = BrokeProtocol::GetPlayersCollection();
        auto* ptr = players->items->pointer();
        const auto size = players->items->size();

        RECT rect;
        GetClientRect(main__window, &rect);

        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;



        auto* pos = UnityTypes::Vector3::make(0, 17, 0);
        Vector3 screenPoint{ -1,-1,-1 };
        BrokeProtocol::get_camera()->worldCamera->worldToScreen_beta({ pos->x,pos->y,pos->z }, &screenPoint, width, height);
        {
            float xz_distance = sqrt(pow(pos->x - local_position->x, 2) + pow(pos->z - local_position->z, 2));
            screenPoint.x *= (xz_distance / (width / 2)) * 44.f;
        }

        DEBUG_LOG("X: " << std::dec << screenPoint.x << " Y: " << screenPoint.y);

        esp_box->set_pos(screenPoint.x - 15.f, screenPoint.y + 15.f);

    	
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
    mono_context->mono_thread_attach(mono_context->mono_get_root_domain());

    BrokeProtocol::show_local_message((char*)"<color=#39d668>[info]</color> GBHRC injected | press <color=#39d668>INSERT</color> to show menu!");
	BrokeProtocol::show_local_message((char*)"<color=#3966d6>[info]</color> join our discord: https://discord.gg/4jRzSHz3 ");
	
    menu = new Application::InteractiveForm();

    MainMenuMarkup(menu, instance);

    Application::register_form(menu);

    menu->hidden = true;

    esp_scene = new Application::Canvas::CanvasForm();
    esp_scene->render_callback = draw_esp;
    esp_scene->hidden = false;
    esp_box = new Application::Canvas::Rectangle{ {0,0},{30,30},{1,1,1} };
    esp_scene->add_elements(1, esp_box);
    esp_scene->update_markup(instance);
	
    instance
        ->append_scene(menu)
		->append_scene(esp_scene);
	
}

void esp_();

void MainThread()
{
    main__window = Hooks::D3D11::FindMainWindow(GetCurrentProcessId());
	
    Application::implement(main__window);
#ifdef _DEBUG
    AllocConsole();
    auto nigger = freopen("CONOUT$", "w", stdout);
    nigger = freopen("CONIN$", "r", stdin);
#endif
	
    Hooks::WndProc::init_hook(main__window);
    Hooks::WndProc::callback(wnd_key_hook);

    mono_context = Mono::Context::get_context();
	
    Hooks::D3D11::hook(Hooks::D3D11::GetPresentAddress(), init_callback);

    //esp_();
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

    	}

        if (wParam == VK_F3)
        {
            BrokeProtocol::GetLocalPlayer()->fire();
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
