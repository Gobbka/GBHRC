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
void wnd_key_hook(UINT msg, WPARAM wParam, LPARAM lParam);
HWND main__window;
Mono::Context* mono_context;

UnityEngine::Transform* aim_target = nullptr;

void __stdcall draw_esp(Application::Render::Scene* pScene)
{
    if(BrokeProtocol::get_manager()->host != nullptr)
	{

        auto* local_player = BrokeProtocol::GetLocalPlayer();
    	
        auto* local_camera = BrokeProtocol::get_camera();
        auto* view_matrix = local_camera->worldCamera->worldToCameraMatrix();
        auto* projection_m = local_camera->worldCamera->projectionMatrix();
        if (local_camera == nullptr)
            return;
        auto* players = BrokeProtocol::GetPlayersCollection();
        auto* ptr = players->items->pointer();
        const auto players_size = players->items->size();
        const auto elements_size = esp_scene->elements_length();

        RECT rect;
        GetClientRect(main__window, &rect);

        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;

        UINT element_index = 0;

        float min_target_distance = 99999.f;
    	
   		for(int i = 0;i<players_size && element_index<elements_size;i++)
   		{
            auto* player = ptr[i];
   			
   			if(player == local_player || player->health == 0.f)
                continue;

            auto* pos = player->rotationT->get_position();

            const auto point_top = Matrix4X4::worldToScreen(view_matrix, projection_m, { pos->x,pos->y+1.5f,pos->z }, { width,height });
   			
            if(point_top.z > 0)
            {
                const auto point_bottom = Matrix4X4::worldToScreen(view_matrix, projection_m, { pos->x,pos->y - player->stance->capsuleHeight,pos->z }, { width,height });
            	
                auto* esp_box = (Application::Canvas::Rectangle*)esp_scene->element_at(element_index);
                esp_box->set_pos(point_top.x, point_top.y);
                esp_box->set_resolution((float)abs(point_top.x - point_bottom.x), (float)abs(point_top.y - point_bottom.y));
                esp_box->render = true;
                element_index++;

                auto distance = sqrt(pow(point_top.x, 2) + pow(point_top.y, 2));
            	if(distance<=300 && distance < min_target_distance)
            	{
                    aim_target = player->rotationT;
                    min_target_distance = distance;
                    esp_box->set_color(0.5f, 0, 0);
            	}else
            	{
                    esp_box->set_color(0, 0.8f, 0);
            	}
            }
   		}

    	for(;element_index<elements_size;element_index++)
    	{
            auto* esp_box = (Application::Canvas::Rectangle*)esp_scene->element_at(element_index);
            esp_box->render = false;
    	}

    	if(min_target_distance == 99999.f)
    	{
            aim_target = nullptr;
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
    ::BrokeProtocol::GetLocalPlayer();
    menu->hidden = true;

    esp_scene = new Application::Canvas::CanvasForm();
    esp_scene->render_callback = draw_esp;
    esp_scene->hidden = false;
	
	for(int i = 0;i<100;i++)
	{
        auto* element = new Application::Canvas::Rectangle{ {0,0},{30,30},{0,0.8,0} };
        element->render = false;
        esp_scene->add_elements(1,element);
	}

    esp_scene->update_markup(instance);
	
	    instance
	        ->append_scene(menu)
			->append_scene(esp_scene);
}

void esp_();

void MainThread()
{
    main__window = Hooks::D3D11::FindMainWindow(GetCurrentProcessId());
    auto* present_address = Hooks::D3D11::GetPresentAddress();
	
    Application::implement(main__window);

    AllocConsole();
    auto nigger = freopen("CONOUT$", "w", stdout);
    nigger = freopen("CONIN$", "r", stdin);

	
    Hooks::WndProc::init_hook(main__window);
    Hooks::WndProc::callback(wnd_key_hook);

    mono_context = Mono::Context::get_context();
    mono_context->mono_thread_attach(mono_context->mono_get_root_domain());
	
    Hooks::D3D11::hook(present_address, init_callback);

    esp_();
}

bool aim_active = false;

void esp_()
{
	while(1)
	{
        if (aim_active==true && aim_target != nullptr)
        {
            auto* local_player = BrokeProtocol::GetLocalPlayer();

            auto* local_camera = BrokeProtocol::get_camera();
            if (local_camera == nullptr)
                return;
            auto* players = BrokeProtocol::GetPlayersCollection();
            auto* ptr = players->items->pointer();
            const auto players_size = players->items->size();

            for (UINT i = 0; i < players_size; i++)
            {
                auto* player = ptr[i];

                if (player == local_player || player->health == 0.f)
                    continue;
            	
                local_player->rotationT->lookAt(player->rotationT);
                BrokeProtocol::GetLocalPlayer()->fire();
            }
            Sleep(5);
        }else
        {
            Sleep(50);
        }

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
        aim_active = true;
	}
	if(msg == WM_LBUTTONUP)
	{
        aim_active = false;
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
