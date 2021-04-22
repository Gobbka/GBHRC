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

HINSTANCE DllInst;
Application::InteractiveForm* menu;
Application::Render::Scene* esp_scene;
void wnd_key_hook(UINT msg, WPARAM wParam, LPARAM lParam);

void draw_esp(Application::Render::Scene* pScene)
{
    if(BrokeProtocol::get_manager()->host != nullptr)
	{
        auto* local_matrix = BrokeProtocol::GetLocalPlayer()->get_worldToLocalMatrix();
        auto* players = BrokeProtocol::GetPlayersCollection();
        auto* ptr = players->items->pointer();
        const auto size = players->items->size();

    	
   		for(int i = 0;i<size;i++)
   		{
   			
   		}
   	}
}

void init_callback(Application::Render::Engine* instance)
{
	
    menu = new Application::InteractiveForm();

    MainMenuMarkup(menu, instance);

    Application::register_form(menu);

    menu->hidden = true;

    esp_scene = new Application::Render::Scene();
    esp_scene->render_callback = draw_esp;
    esp_scene->hidden = false;
    esp_scene->alloc_vbuffer(instance);
	
    instance
        ->append_scene(menu)
		->append_scene(esp_scene);
	
}

void esp_();

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
            auto* matrix = BrokeProtocol::GetLocalPlayer()->get_worldToLocalMatrix();

            system("cls");
    		
            DEBUG_LOG(
                matrix->matrix[0][0] << " " << matrix->matrix[0][1] << " " << matrix->matrix[0][2] << " " << matrix->matrix[0][3] << "\n" <<
                matrix->matrix[1][0] << " " << matrix->matrix[1][1] << " " << matrix->matrix[1][2] << " " << matrix->matrix[1][3] << "\n" <<
                matrix->matrix[2][0] << " " << matrix->matrix[2][1] << " " << matrix->matrix[2][2] << " " << matrix->matrix[2][3] << "\n" <<
                matrix->matrix[3][0] << " " << matrix->matrix[3][1] << " " << matrix->matrix[3][2] << " " << matrix->matrix[3][3]
            );
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
