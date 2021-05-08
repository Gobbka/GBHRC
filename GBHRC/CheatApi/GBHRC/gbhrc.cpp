#include "gbhrc.h"

#include <codecvt>

#include "../../resource.h"
#include <SpriteFont.h>
#include "Render/Engine/Engine.h"
#include "../BrokeProtocol/BrokeProtocol.h"
#include "../Tools/3dMatrix.h"
#include "Form/Canvas/elements/rectangle/rectangle.h"
#include "Application.h"
#include "Render/Text/Text.h"

GBHRC::Context::Context()
{
	this->config = new Config();
}

void GBHRC::Context::draw_esp(Application::Render::Scene* pScene,Application::Render::Engine*engine)
{

    static DirectX::SpriteFont* esp_font = engine->create_font(
        (void*)LoadResource(DllInst, FindResourceW(DllInst, MAKEINTRESOURCEW(IDR_VISBY_ROUND), L"SPRITEFONT")),
        0x6608
    );

    {
        static auto* text = new Application::Render::Text{
            engine->create_font(
				(void*)LoadResource(DllInst, FindResourceW(DllInst, MAKEINTRESOURCEW(IDR_VISBY_ROUND), L"SPRITEFONT")),0x6608
            ),
        	Application::Render::TextAlign::Center,{0,0}
        };
        text->set_text( "nigger");
    	
        text->DrawInRect(engine,{500,40});
    }
	
    if (this->config->esp_active && BrokeProtocol::get_manager() != nullptr && BrokeProtocol::get_manager()->host != nullptr)
    {
        auto* local_player = BrokeProtocol::GetLocalPlayer();

        auto* local_camera = BrokeProtocol::get_camera();
        auto* view_matrix = local_camera->worldCamera->worldToCameraMatrix();
        auto* projection_m = local_camera->worldCamera->projectionMatrix();

        auto* players = BrokeProtocol::GetPlayersCollection();
        auto* ptr = players->items->pointer();
        const auto players_size = players->items->size();
        const auto elements_size = esp_boxes.size();

        const Application::Render::Resolution camera_resolution = { local_camera->worldCamera->get_pixelWidth() ,local_camera->worldCamera->get_pixelHeight() };

        UINT element_index = 0;

        float min_target_distance = 99999.f;
        EspBox* min_target_box=nullptr;

        engine->get_batch()->Begin();

        for (int i = 0; i < players_size && element_index < elements_size; i++)
        {
            auto* player = ptr[i];

            if (player == local_player || player->health == 0.f)
                continue;

            auto* pos = player->rotationT->get_position();

            const auto point_top = Matrix4X4::worldToScreen(view_matrix, projection_m, { pos->x,pos->y + 1.5f,pos->z }, camera_resolution);

            if (point_top.z > 0)
            {
                const auto point_bottom = Matrix4X4::worldToScreen(view_matrix, projection_m, { pos->x,pos->y - player->stance->capsuleHeight,pos->z }, camera_resolution);

                const auto player_height = round(abs(point_top.y - point_bottom.y));
            	
                auto* esp_box = this->esp_boxes[element_index];
                {
                    //auto* box = esp_box->box;
                    //box->set_pos(point_top.x, point_top.y);
                    //box->set_resolution((float)abs(point_top.x - point_bottom.x), (float)abs(point_top.y - point_bottom.y));
                    //box->render = true;
                }
            	if(this->config->esp_health_active)
                {
                    auto* max_h_box = esp_box->max_health_box;
                    max_h_box->set_pos(point_top.x, point_top.y);
                    max_h_box->set_resolution(10, player_height-1);
                    max_h_box->render = true;

                    auto* h_box = esp_box->health_box;

                    const auto nigger = player_height * (player->health / player->healthLimit);
                	
                    h_box->set_pos(point_top.x, point_top.y - (player_height - nigger));
                	
                    h_box->set_resolution(10, nigger);
                    h_box->render = true;
                }
                element_index++;

                auto rect = esp_font->MeasureDrawBounds((wchar_t*)player->username->array, DirectX::XMFLOAT2(0,0));

            	if(this->config->esp_draw_name)
	                esp_font->DrawString(
	                    engine->get_batch(),
	                    (wchar_t*)&player->username->array,
	                    DirectX::XMFLOAT2(
	                        point_top.x + camera_resolution.width/2 - (rect.right) / 2 * 0.5f,
                            camera_resolution.height/2 - point_top.y - (rect.bottom) * 0.5
	                    ),
	                    DirectX::Colors::White, 
	                    0.0f,
	                    DirectX::XMFLOAT2(0.0f, 0.0f),
	                    DirectX::XMFLOAT2(0.5f, 0.5f)
	                );
            	
                if(this->config->esp_draw_gun_name)
	                esp_font->DrawString(
	                    engine->get_batch(),
	                    (wchar_t*)&player->curEquipable->itemName->array,
	                    DirectX::XMFLOAT2(
	                        point_bottom.x + camera_resolution.width / 2 - (rect.right) / 2 * 0.5f,
	                        camera_resolution.height / 2 - point_bottom.y + (rect.bottom) * 0.5f
	                    ),
	                    DirectX::Colors::White,
	                    0.0f,
	                    DirectX::XMFLOAT2(0.0f, 0.0f),
	                    DirectX::XMFLOAT2(0.5, 0.5)
	                );
            	
                if (this->config->aim_assist) {
                	
                    auto distance = sqrt(pow(point_top.x, 2) + pow(point_top.y, 2));
                    if (distance <= this->config->fov_size && distance < min_target_distance)
                    {
                        aim_target = player->rotationT;
                        min_target_distance = distance;
                        min_target_box = esp_box;
                    }
                }
            	
                esp_box->box->set_color(0, 0.8f, 0);
            }
        }

        engine->get_batch()->End();

        for (; element_index < elements_size; element_index++)
        {
            //auto* esp_box = (Application::Canvas::Rectangle*)esp_scene->element_at(element_index);
            auto* esp_box = this->esp_boxes[element_index];
            esp_box->box->render = false;
            esp_box->max_health_box->render = false;
            esp_box->health_box->render = false;
        	
        }

        if (min_target_box == nullptr)
        {
            aim_target = nullptr;
        }else
        {
            min_target_box->box->set_color(0.5f, 0, 0);
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

void GBHRC::Context::set_esp_scene(Application::Canvas::CanvasForm* form)
{
    this->esp_scene = form;
}

void GBHRC::Context::static_draw_callback(Application::Render::Scene* pScene,Application::Render::Engine*engine)
{
    auto* context = GBHRC::Context::instance();
    context->draw_esp(pScene,engine);
}

void GBHRC::Context::life_cycle()
{
	while(true)
	{
		
       if (aim_active==true && aim_target != nullptr)
       {
           auto* local_player = BrokeProtocol::GetLocalPlayer();

           local_player->rotationT->lookAt(aim_target);
           
           Sleep(5);
       }else
       {
           Sleep(50);
       }

	}
}
