
#include <cstdio>

#include "includes/win.h"
#include "CheatApi/Hooks/d3d11/d3d11hook.h"
#include "CheatApi/Hooks/wndproc/wndprochook.h"

#include "Form/Interactive/InteractiveForm.h"

#include "Forms/Menu/MenuMain.h"

#include "CheatApi/BrokeProtocol/Mono/Mono.h"
#include "CheatApi/BrokeProtocol/BrokeProtocol.h"

#include "CheatApi/GBHRC/gbhrc.h"

#include <string>
#include <sstream>

#include "resource.h"
#include "includes/clientdefs.h"

#include "Asserts/VersionAssert/ClientVersionAssers.h"
#include "Forms/test/testScene.h"
#include <fstream>

HINSTANCE DllInst;
Application::InteractiveForm* menu;
//Application::InteractiveForm* friend_list;
Application::Render::CanvasScene* esp_scene;
Application::Render::CanvasScene* test_scene;
void wnd_key_hook(UINT msg, WPARAM wParam, LPARAM lParam);
HWND main__window;

DEFINE_LOGGER()


DirectX::SpriteFont* VisbyRoundCFFont;

extern Mono::Context* MonoContext;


void init_callback(Application::Render::Engine* instance)
{
    DEBUG_LOG("INIT CALLBACK");
    MonoContext->mono_thread_attach(MonoContext->mono_get_root_domain());

    BrokeProtocol::show_local_message((char*)"<color=#39d668>[info]</color> GBHRC injected | press <color=#39d668>INSERT</color> to show menu!");
	BrokeProtocol::show_local_message((char*)"<color=#3966d6>[info]</color> join our discord: " DISCORD_CHANNEL);

    VisbyRoundCFFont = instance->create_font(
        (void*)LoadResource(DllInst, FindResourceW(DllInst, MAKEINTRESOURCEW(IDR_VISBY_ROUND), L"SPRITEFONT")),
        0x6608
    );

    DEBUG_LOG("USER WELCOMED");
	
    menu = Application::Context::create_form();
    //friend_list = Application::Context::create_form();

    MainMenuMarkup(menu);
    //FiendListMarkup(friend_list, instance);

    menu->hide();
    //friend_list->hidden = true;

    //DEBUG_LOG("MENU FORM REGISTERED");
	
    esp_scene = Application::Context::create_canvas();
    esp_scene->render_callback = GBHRC::Context::static_draw_callback;
    esp_scene->show();
    GBHRC::Context::instance()->set_esp_scene(esp_scene);
    GBHRC::Context::instance()->make_esp_boxes();

    test_scene = new Application::Render::CanvasScene(instance);
    TestSceneMarkup(test_scene,instance);
    test_scene->render_callback = test_scene_draw;

    DEBUG_LOG("ESP REGISTERED");

    DEBUG_LOG("SCENE'S APPENDED");

    //esp_scene->initialize_components(instance);

	//
	// LUA TEST
#ifdef LUA_SUPPORT
    LuaEngine::Context::execute((char*)LoadResource(DllInst, FindResourceW(DllInst, MAKEINTRESOURCEW(IDR_TEXT1), L"TEXT")));
#endif
}


void MainThread()
{
	
    main__window = Hooks::D3D11::FindMainWindow(GetCurrentProcessId());
	
    EMBED_LOGGER();
	
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


    {
        Hooks::WndProc::init_hook(main__window);
        Hooks::WndProc::callback(wnd_key_hook);
    }
	
	
    Hooks::D3D11::fnPresent present_address;
    auto hr = Hooks::D3D11::GetPresentAddress(&present_address);

    Application::Context::implement(main__window);

    if (FAILED(hr))
    {
        DEBUG_LOG("CANNOT GET PRESENT ADDRESS: " << std::hex << hr);
        return;
    }

    Hooks::D3D11::hook(present_address, init_callback);

    {
        auto context = GBHRC::Context::instance();
        context->implement(DllInst);
        context->life_cycle();
    }
}

extern Application::Context* AppContext;

void wnd_key_hook(UINT msg, WPARAM wParam, LPARAM lParam)
{
    AppContext->window_proc(msg, wParam, lParam);

    if (msg == WM_KEYUP)
    {
        if (wParam == VK_DELETE)
        {

        }

        if (wParam == VK_INSERT)
        {
            bool state = menu->hidden();
            state ? menu->show() : menu->hide();
            
            //friend_list->hidden = !state;
            Hooks::WndProc::setInputState(!state);
        }

        if(GBHRC::Context::instance()->config->fly_active)
        {
            if (wParam == VK_CONTROL)
            {
                auto* rigid_body = BrokeProtocol::GetLocalPlayer()->positionRB;
                auto* vector = rigid_body->get_velocity();
                vector->y *= -1;
                rigid_body->add_force(0, vector->y, 0);
            }

            if (wParam == VK_SPACE)
            {
                auto* rigid_body = BrokeProtocol::GetLocalPlayer()->positionRB;
                auto* vector = rigid_body->get_velocity();
                vector->y *= -1;
                rigid_body->add_force(0, vector->y, 0);
            }
        }

        if (wParam == VK_F5)
        {
            BrokeProtocol::send_global_chat((char*)"nigger");
        }

        if(wParam == VK_F4)
        {
            BrokeProtocol::GetLocalPlayer()->clear_injuries();
        }

    	if(wParam == VK_F2){

            if (BrokeProtocol::GetLocalPlayer()->otherEntity == nullptr)
                return;
    		
            auto* items = BrokeProtocol::GetLocalPlayer()->otherEntity->myItems;
            auto* values = items->get_values();

            if (items->count <= 0)
                return;
    		
            auto*array= MonoContext->mono_array_new(
                MonoContext->mono_get_root_domain(),
                MonoContext->mono_class_from_name(MonoContext->get_script_image(), "BrokeProtocol.Utility", "InventoryItem"),
                items->count
            );

            values->copy_to(array, 0);
            auto* mono_context = Mono::Context::get_context();
    		
    		for(int i = items->count; i --> 0;)
    		{
                auto* inv_item = (BrokeProtocol::Structs::InventoryItem*)array->vector[i];
                auto* item = inv_item->item;

                Mono::MonoArray* theArray = mono_context->mono_array_new(mono_context->mono_get_root_domain(), mono_context->get_object_class(), 3);
                theArray->vector[0] = mono_context->make_byte(11);
                theArray->vector[1] = mono_context->make_int(item->index);
                theArray->vector[2] = mono_context->make_int(inv_item->count);

                BrokeProtocol::SendToServer(BrokeProtocol::PacketFlags::Reliable, BrokeProtocol::SvPacket::TransferSearch, theArray);
    		}
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
