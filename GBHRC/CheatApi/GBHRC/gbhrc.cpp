#include "gbhrc.h"

#include <codecvt>

#include "../../resource.h"
#include <SpriteFont.h>
#include "Render/Engine/Engine.h"
#include "../BrokeProtocol/BrokeProtocol.h"
#include "../Tools/3dMatrix.h"
#include "Form/Canvas/elements/rectangle/rectangle.h"
#include "FloatColors.h"
#include "../BrokeProtocol/classes/Guns/ShBallistic.h"
#include "../LuaEngine/LuaEngine.h"
#include "../PipeServer/PipeServer.h"
#include "Render/Text/Text.h"

extern DirectX::SpriteFont* VisbyRoundCFFont;

GBHRC::Context::Context()
{
	this->config = new Config();
}



void GBHRC::Context::render_callback(Application::Render::DrawEvent* event)
{
    if(BrokeProtocol::get_manager() != nullptr && BrokeProtocol::get_manager()->host != nullptr)
    {
        auto* local_player = BrokeProtocol::GetLocalPlayer();
        if (local_player == nullptr)
            return;
        auto* local_pos = local_player->rotationT->get_position();
        auto* local_camera = BrokeProtocol::get_camera();
        auto* view_matrix = local_camera->worldCamera->worldToCameraMatrix();
        auto* projection_m = local_camera->worldCamera->projectionMatrix();
        auto  camera_resolution = Application::Render::Resolution{ (UINT)local_camera->worldCamera->get_pixelWidth() ,(UINT)local_camera->worldCamera->get_pixelHeight() };

        auto player_iterator = BrokeProtocol::GetPlayersCollection()->items->iterator();

        const auto elements_size = esp_boxes.size();
        UINT element_index = 0;
    	
        EspBox* min_target_box = nullptr;
        EspPlayer min_aimbot_target{ nullptr };
    	
        while (player_iterator.next())
        {
            EspPlayer player;
            {
                auto* sh_player = player_iterator.item();
            	if(sh_player == local_player || sh_player->health <= 0)
                    continue;
                auto* pos = sh_player->rotationT->get_position();
                const auto point_top = Matrix4X4::worldToScreen(view_matrix, projection_m, { pos->x,pos->y + 1.5f,pos->z }, camera_resolution);

                if (point_top.z < 0)
                    continue;
            	
                player = { sh_player,point_top,0,0,0};
            }
        	
        	// draw player
            if (this->config->esp_active)
            {
                auto* pos = player.player->rotationT->get_position();
                player.bottom_point = Matrix4X4::worldToScreen(view_matrix, projection_m, { pos->x,pos->y - player.player->stance->capsuleHeight,pos->z }, camera_resolution);
                player.display_distance = sqrt(pow(player.top_point.x, 2) + pow(player.top_point.y, 2));
                player.map_distance = sqrt(pow(local_pos->x - pos->x, 2) + pow(local_pos->z - pos->z, 2));
            	
                this->draw_player(event,element_index, camera_resolution, &player);
            }

        	// check player for aim target status
        	if(this->config->aim_assist)
        	{
        		if(player.top_point.z > 0 && this->is_aim_target(&min_aimbot_target,&player))
        		{
                    min_aimbot_target = player;
                    min_target_box = this->esp_boxes[element_index];
        			
                    this->aim_target = player.player->rotationT;
        		}
        	}

            element_index++;
        }

        for (; element_index < elements_size; element_index++)
        {
            auto* esp_box = this->esp_boxes[element_index];
            esp_box->box->render = false;
            esp_box->max_health_box->render = false;
            esp_box->health_box->render = false;
        }

        if (min_target_box == nullptr)
        {
            aim_target = nullptr;
        }
        else
        {
            min_target_box->box->set_color({ 0.5f, 0, 0 });
        }
    }
}

void GBHRC::Context::draw_player(Application::Render::DrawEvent* event,UINT element_index,Application::Render::Resolution camera_resolution ,EspPlayer* player)
{
    if (player->top_point.z <= 0)
        return;
	
    auto* engine = event->engine;

    auto point_top = player->top_point;
    auto point_bottom = player->bottom_point;
	
    const auto player_height = round(abs(point_top.y - point_bottom.y));

    auto* esp_box = this->esp_boxes[element_index];
    {
        //auto* box = esp_box->box;
        //box->set_pos(point_top.x, point_top.y);
        //box->set_resolution((float)abs(point_top.x - point_bottom.x), (float)abs(point_top.y - point_bottom.y));
        //box->render = true;
    }
    if (this->config->esp_health_active)
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

    if (this->config->esp_draw_name)
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

    if (this->config->esp_draw_gun_name)
        VisbyRoundCFFont->DrawString(
            engine->get_batch(),
            (wchar_t*)&player->player->curEquipable->itemName->array,
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
            new_player->display_distance <= this->config->fov_size &&
            new_player->display_distance <= old_player->display_distance
            );
    }

	return new_player->display_distance <= this->config->fov_size;
}

void GBHRC::Context::set_esp(bool status)
{
    this->config->esp_active = status;
    this->config->esp_health_active = status;
    this->config->esp_draw_gun_name = status;
    this->config->esp_draw_name = status;

	if(status == false)
	{
		for(auto*element:this->esp_boxes)
		{
            element->box->render = false;
            element->health_box->render = false;
            element->max_health_box->render = false;
		}
	}
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
        esp_scene->add_element(element);

        auto* max_health = new Application::Canvas::Rectangle{ {0,0},{30,10},{1.f,0,0} };
        max_health->render = false;
        max_health->wireframed = false;
        esp_scene->add_element(max_health);

        auto* health = new Application::Canvas::Rectangle{ {0,0},{30,10},{0,0.8,0} };
        health->render = false;
        health->wireframed = false;
        esp_scene->add_element(health);

        this->esp_boxes.push_back(
            new EspBox{
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
    auto* pipe_server = PipeServer::create("");
	
	while(true)
	{
        if (BrokeProtocol::get_manager() != nullptr && BrokeProtocol::get_manager()->host != nullptr)
        {
            auto* local_player = BrokeProtocol::GetLocalPlayer();

            if (config->fly_active && GetAsyncKeyState(VK_SPACE))
            {
                local_player->jump();
            }

            if (config->car_speed && local_player->curMount != nullptr)
            {
                local_player->curMount->maxSpeed = 500.f;
                local_player->curMount->speedLimit = 500.f;
            }

        	if(config->no_recoil && local_player->curEquipable != nullptr)
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

            if (config->aim_assist == true && aim_active && aim_target != nullptr)
            {
                local_player->rotationT->lookAt(aim_target);

                Sleep(5);
                continue;
            }
        }

        char buffer[1024];
        auto bytes_received = pipe_server->receive(buffer, 1024);
		
		if(bytes_received>0)
		{
            DEBUG_LOG("BYTES RECEIVED..");
		}

        Sleep(50);
    }
}
