#include "gbhrc.h"

#include <codecvt>

#include "../../resource.h"
#include <SpriteFont.h>
#include "Render/Engine/Engine.h"
#include "../BrokeProtocol/BrokeProtocol.h"
#include "../Tools/3dMatrix.h"
#include "Form/Canvas/elements/rectangle/rectangle.h"

GBHRC::Context::Context()
{
	this->config = new Config();
}

void GBHRC::Context::draw_esp(Application::Render::Scene* pScene,Application::Render::Engine*engine)
{
    auto* esp_scene = (Application::Canvas::CanvasForm*)pScene;

    static DirectX::SpriteFont* esp_font;
	
	if(esp_font == nullptr)
	{
        auto* nigger = LoadResource(DllInst, FindResourceW(DllInst, MAKEINTRESOURCEW(IDR_VISBY_ROUND), L"SPRITEFONT"));
		if(nigger == nullptr)
		{
            DEBUG_LOG("CANNOT CREATE FONT");
            return;
		}
        esp_font = new DirectX::SpriteFont(engine->pDevice, (uint8_t*)nigger, 0x6608);

        esp_font->SetDefaultCharacter('?');
	}
    
    engine->get_batch()->Begin();

    engine->get_batch()->End();
	
    if (BrokeProtocol::get_manager()->host != nullptr)
    {
        auto* local_player = BrokeProtocol::GetLocalPlayer();

        auto* local_camera = BrokeProtocol::get_camera();
        auto* view_matrix = local_camera->worldCamera->worldToCameraMatrix();
        auto* projection_m = local_camera->worldCamera->projectionMatrix();

        auto* players = BrokeProtocol::GetPlayersCollection();
        auto* ptr = players->items->pointer();
        const auto players_size = players->items->size();
        const auto elements_size = esp_scene->elements_length();

        const auto width = local_camera->worldCamera->get_pixelWidth();
        const auto height = local_camera->worldCamera->get_pixelHeight();

        UINT element_index = 0;

        float min_target_distance = 99999.f;
        Application::Canvas::Rectangle* min_target_box=nullptr;

        engine->get_batch()->Begin();


        for (int i = 0; i < players_size && element_index < elements_size; i++)
        {
            auto* player = ptr[i];

            if (player == local_player || player->health == 0.f)
                continue;

            auto* pos = player->rotationT->get_position();

            const auto point_top = Matrix4X4::worldToScreen(view_matrix, projection_m, { pos->x,pos->y + 1.5f,pos->z }, { width,height });

            if (point_top.z > 0)
            {
                const auto point_bottom = Matrix4X4::worldToScreen(view_matrix, projection_m, { pos->x,pos->y - player->stance->capsuleHeight,pos->z }, { width,height });

                auto* esp_box = (Application::Canvas::Rectangle*)esp_scene->element_at(element_index);
                esp_box->set_pos(point_top.x, point_top.y);
                esp_box->set_resolution((float)abs(point_top.x - point_bottom.x), (float)abs(point_top.y - point_bottom.y));
                esp_box->render = true;
                element_index++;

                auto rect = esp_font->MeasureDrawBounds((wchar_t*)player->username->array, DirectX::XMFLOAT2(point_top.x + width / 2, height / 2 - point_top.y));
            	
                esp_font->DrawString(
                    engine->get_batch(),
                    (wchar_t*)&player->username->array,
                    DirectX::XMFLOAT2(
                        point_top.x + width/2 - (rect.right - rect.left)/2, 
                        height/2 - point_top.y - (rect.bottom - rect.top)
                    ),
                    DirectX::Colors::Green, 0.0f,
                    DirectX::XMFLOAT2(0.0f, 0.0f),
                    DirectX::XMFLOAT2(1.0f, 1.0f)
                );

                auto distance = sqrt(pow(point_top.x, 2) + pow(point_top.y, 2));
                if (distance <= 300 && distance < min_target_distance)
                {
                    aim_target = player->rotationT;
                    min_target_distance = distance;
                    min_target_box = esp_box;
                }

                esp_box->set_color(0, 0.8f, 0);
            }
        }

        engine->get_batch()->End();

        for (; element_index < elements_size; element_index++)
        {
            auto* esp_box = (Application::Canvas::Rectangle*)esp_scene->element_at(element_index);
            esp_box->render = false;
        }

        if (min_target_box == nullptr)
        {
            aim_target = nullptr;
        }else
        {
            min_target_box->set_color(0.5f, 0, 0);
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
