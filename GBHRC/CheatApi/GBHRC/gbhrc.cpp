#include "gbhrc.h"

#include <codecvt>
#include <ctime>

#include "../../resource.h"
#include <SpriteFont.h>
#include "Render/Engine/Engine.h"
#include "../BrokeProtocol/BrokeProtocol.h"
#include "../Tools/3dMatrix.h"
#include "Form/Canvas/elements/rectangle/rectangle.h"
#include "FloatColors.h"
#include "../BrokeProtocol/classes/Guns/ShBallistic.h"
#include "../LuaEngine/LuaEngine.h"
#include "Render/Scene/CanvasScene.h"
#include "Render/Text/Text.h"
#include "../BrokeProtocol/Mono/Mono.h"

extern DirectX::SpriteFont* VisbyRoundCFFont;

#ifdef LUA_SUPPORT
#include "../PipeServer/PipeServer.h"

void GBHRC::Context::receive_lua_thread()
{
    auto context  = Mono::Context::get_context();

    context->mono_thread_attach(context->mono_get_root_domain());
    auto* pipe_server = PipeServer::create("");

	while(true)
	{
        char* buffer = nullptr;
        auto bytes_received = pipe_server->receive(&buffer);

        if (bytes_received > 0)
        {
            DEBUG_LOG("[GBHRC] RECEIVED LUA SCRIPT");
            LuaEngine::Context::execute(buffer);
        }

        Sleep(50);
	}
}

#endif

void GBHRC::EspBox::disable()
{
    this->box->render = false;
    this->health_box->render = false;
    this->max_health_box->render = false;
}

bool GBHRC::EspPlayer::apply_box(Matrix4X4* view_matrix, Matrix4X4* projection_matrix,
                                 Application::Render::Resolution camera_resolution)
{
    auto* pos = this->player->rotationT->get_position();
    auto box_top_pos = Matrix4X4::worldToScreen(view_matrix, projection_matrix, { pos->x,pos->y + 1.5f,pos->z }, camera_resolution);

    if (box_top_pos.z < 0)
        return false;

    auto box_bottom_pos = Matrix4X4::worldToScreen(view_matrix, projection_matrix, { pos->x,pos->y - player->stance->capsuleHeight,pos->z }, camera_resolution);
	
    box->box_position = { box_top_pos.x,box_top_pos.y };
    box->box_resolution = { (UINT)round(abs(box_top_pos.x - box_bottom_pos.x)),(UINT)round(abs(box_top_pos.y - box_bottom_pos.y)) };
    return true;
}

GBHRC::EspPlayer::EspPlayer(EspBox* box)
{
    this->box = box;
    this->player = nullptr;
    this->display_distance = 0;
    this->map_distance = 0;
}

GBHRC::Context::Context()
{
	this->config = new Config();
}



void GBHRC::Context::render_callback(Application::Render::DrawEvent* event)
{
    if(BrokeProtocol::get_manager() != nullptr && BrokeProtocol::get_manager()->host != nullptr)
    {
        auto* local_player = BrokeProtocol::GetLocalPlayer();
        if (local_player == nullptr) return;

        auto* local_camera = BrokeProtocol::get_camera();
    	
        auto* view_matrix = local_camera->worldCamera->worldToCameraMatrix();
        auto* projection_m = local_camera->worldCamera->projectionMatrix();
        auto  camera_resolution = Application::Render::Resolution{ (UINT)local_camera->worldCamera->get_pixelWidth() ,(UINT)local_camera->worldCamera->get_pixelHeight() };

        auto player_iterator = BrokeProtocol::GetPlayersCollection()->items->iterator();

        UINT element_index = 0;
    	
        EspPlayer min_aimbot_target(nullptr);
    	
        while(player_iterator.next())
        {
            EspPlayer player(nullptr);
            {
                auto* sh_player = player_iterator.item();
            	if(sh_player == local_player || sh_player == nullptr || sh_player->health <= 0)
                    continue;

                player.player = sh_player;
                player.box = this->esp_boxes[element_index];

                if(!player.apply_box(view_matrix,projection_m,camera_resolution))
                    continue;
            }
        	
        	// draw player
            if (this->config->esp.active)
            {            	
                this->draw_player(event, camera_resolution, &player);
            }else
            {
                player.box->disable();
            }

        	// check player for aim target status
        	if(this->config->aim.assist)
        	{
                player.display_distance = sqrt(pow(player.box->box_position.x, 2) + pow(player.box->box_position.y, 2));
        		
        		if(this->is_aim_target(&min_aimbot_target,&player))
        		{	
                    min_aimbot_target = player;
        			
                    this->aim_target = player.player->rotationT;
        		}
        	}

            element_index++;
        }

        for (; element_index < esp_boxes.size(); element_index++)
        {
            this->esp_boxes[element_index]->disable();
        }

        if (min_aimbot_target.player == nullptr)
        {
            aim_target = nullptr;
        }
        else
        {
            min_aimbot_target.box->box->set_color({ 0.5f, 0, 0 });
        }

    }
}

void GBHRC::Context::draw_player(Application::Render::DrawEvent* event,Application::Render::Resolution camera_resolution ,EspPlayer* player)
{
	
    auto* engine = event->engine;
	
    const auto player_height = player->box->box_resolution.height;

    auto* esp_box = player->box;

    auto point_top = esp_box->box_position;
    Application::Render::Position point_bottom = {point_top.x,point_top.y - player_height};
	
    if (this->config->esp.draw_health)
    {
        auto* max_h_box = esp_box->max_health_box;
        max_h_box->set_pos(point_top.x,point_top.y);
        max_h_box->set_resolution(10, player_height - 1);
        max_h_box->render = true;

        auto* h_box = esp_box->health_box;

        const auto nigger = player_height * (player->player->health / player->player->healthLimit);

        h_box->set_pos(point_top.x, point_top.y - (player_height - nigger));

        h_box->set_resolution(10, nigger);
        h_box->render = true;
    }else
    {
        esp_box->disable();
    }

    if (this->is_friend((wchar_t*)&player->player->username->array))
    {
        esp_box->health_box->set_color({COLOR_FROM_RGB(75, 128, 207)});
    }else
    {
        esp_box->health_box->set_color({COLOR_FROM_RGB(0, 204, 0)});
    }

    event->engine->get_batch()->Begin();
	
    auto rect = VisbyRoundCFFont->MeasureDrawBounds((wchar_t*)player->player->username->array, DirectX::XMFLOAT2(0, 0));

    if (this->config->esp.draw_name)
        VisbyRoundCFFont->DrawString(
            engine->get_batch(),
            (wchar_t*)&player->player->username->array,
            DirectX::XMFLOAT2(
                point_top.x + camera_resolution.width / 2 - (rect.right) / 2 * 0.5f,
                camera_resolution.height / 2 - point_top.y - (rect.bottom) * 0.5
            ),
            DirectX::Colors::White,
            0.0f,
            DirectX::XMFLOAT2(0.0f, 0.0f),
            DirectX::XMFLOAT2(0.5f, 0.5f)
        );
	
    auto* eq_name = (wchar_t*)&player->player->curEquipable->itemName->array;
    if (this->config->esp.draw_gun_name && eq_name)
        VisbyRoundCFFont->DrawString(
            engine->get_batch(),
            eq_name,
            DirectX::XMFLOAT2(
                point_bottom.x + camera_resolution.width / 2 - (rect.right) / 2 * 0.5f,
                camera_resolution.height / 2 - point_bottom.y + (rect.bottom) * 0.5f
            ),
            DirectX::Colors::White,
            0.0f,
            DirectX::XMFLOAT2(0.0f, 0.0f),
            DirectX::XMFLOAT2(0.5, 0.5)
        );
    event->engine->get_batch()->End();
}

bool GBHRC::Context::is_aim_target(EspPlayer* old_player, EspPlayer* new_player) const
{
	if(old_player->player!=nullptr)
	{
        return (
            new_player->display_distance <= this->config->aim.fov_size &&
            new_player->display_distance <= old_player->display_distance
            );
    }

	return new_player->display_distance <= this->config->aim.fov_size;
}

void GBHRC::Context::set_speed_hack(bool enable)
{
    this->config->player_speed = enable;
}

void GBHRC::Context::set_fly(bool enable)
{
    auto* shManager = BrokeProtocol::get_manager();
    if (shManager != nullptr && shManager->host != nullptr)
    {
        BrokeProtocol::GetLocalPlayer()->positionRB->set_use_gravity(!enable);
    }
    this->config->fly_active = enable;

}

void GBHRC::Context::set_esp(bool status)
{
    this->config->esp.active = status;

	if(status == false)
		for(auto*element:this->esp_boxes)
            element->disable();
}

bool GBHRC::Context::is_friend(wchar_t* nickname)
{
	for (auto* friendn : this->friend_list)
	{
        if (wcscmp(nickname, friendn) == 0)
            return true;
	}
    return false;
}

void GBHRC::Context::add_friend(wchar_t* nickname)
{
    this->friend_list.push_back(nickname);
}

void GBHRC::Context::remove_friend(wchar_t* nickname)
{
    for(int i =0;i<friend_list.size();i++)
    {
        auto* name = friend_list[i];
        if (wcscmp(name, nickname) == 0)
        {
            this->friend_list.erase(friend_list.begin() + i);
            return;
        }
    }
}

void GBHRC::Context::implement(HMODULE DllInst)
{
    this->DllInst = DllInst;
}

GBHRC::Context* GBHRC::Context::instance()
{
	static auto* gbhrc_context = new Context{};
	return gbhrc_context;
}

void GBHRC::Context::make_esp_boxes()
{
    for (int i = 0; i < 100; i++)
    {
        auto* element = new Application::Canvas::Rectangle{ {0,0},{30,30},{0,0.8,0} };
        element->render = false;
        element->wireframed = true;
        esp_scene->add_canvas_element(element);

        auto* max_health = new Application::Canvas::Rectangle{ {0,0},{30,10},{1.f,0,0} };
        max_health->render = false;
        max_health->wireframed = false;
        esp_scene->add_canvas_element(max_health);

        auto* health = new Application::Canvas::Rectangle{ {0,0},{30,10},{0,0.8,0} };
        health->render = false;
        health->wireframed = false;
        esp_scene->add_canvas_element(health);

        this->esp_boxes.push_back(
            new EspBox{
            	{0,0},
            	{0,0},
                element,
                max_health,
            	health
            }
        );
    }
}

void GBHRC::Context::set_esp_scene(Application::Render::CanvasScene* form)
{
    this->esp_scene = form;
}

void GBHRC::Context::static_draw_callback(Application::Render::DrawEvent* event)
{
    auto* context = GBHRC::Context::instance();
    context->render_callback(event);
}

void GBHRC::Context::life_cycle()
{
	
#ifdef LUA_SUPPORT
    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)GBHRC::Context::receive_lua_thread, nullptr, 0, nullptr);
#endif
	
	while(true)
	{
		
		
        auto* shManager = BrokeProtocol::get_manager();
        if (shManager != nullptr && shManager->host != nullptr)
        {
            auto* local_player = BrokeProtocol::GetLocalPlayer();
        	if(local_player == nullptr)
                continue;
            UnityTypes::RigidBody* positionRB = local_player->curMount == nullptr ? local_player->positionRB : local_player->curMount->positionRB;

            local_player->weightLimit = 9999999.f;


            if (config->fly_active )
            {
                positionRB->set_use_gravity(false);
            	
                if(GetAsyncKeyState(VK_SPACE))
                {
                    positionRB->add_force(0, 0.5f, 0);
                }
            	if(GetAsyncKeyState(VK_CONTROL))
            	{
                    positionRB->add_force(0, -0.5f, 0);
            	}
            }

        	
            if(config->player_speed && local_player->mode && local_player->curMount == nullptr)
            {
                local_player->speed = 46;
                local_player->speedLimit = 46;
            	
            	if(!config->fly_active)
					positionRB->add_force(0, -5, 0);
            }else
            {
                local_player->speed      = 12;
                local_player->speedLimit = 12;
            }
        	
            if (config->car_speed && local_player->curMount != nullptr)
            {
                local_player->curMount->speed = 500.f;
                local_player->curMount->speedLimit = 500.f;
            }

        	if(config->aim.no_recoil && local_player->curEquipable != nullptr)
        	{
                auto* weapon = BrokeProtocol::GetLocalPlayer()->current_weapon();

                if (weapon->ammoItem != nullptr)
                {
                    // weapon can fire
                    auto fire_weapon = (BrokeProtocol::ShBallistic*)weapon;
                    fire_weapon->accuracy = 0;
                    fire_weapon->recoil = 0;
                    fire_weapon->range = 6000;
                }
        	}

            if (config->aim.assist == true && aim_active && aim_target != nullptr)
            {
                local_player->rotationT->lookAt(aim_target);

                continue;
            }

            Sleep(5);
        }
    }
}
