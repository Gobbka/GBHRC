#include "gbhrc.h"


#include "../BrokeProtocol/BrokeProtocol.h"
#include "../Tools/3dMatrix.h"
#include "Form/Canvas/elements/rectangle/rectangle.h"


GBHRC::Context::Context()
{
	this->config = new Config();
}

void GBHRC::Context::draw_esp(Application::Render::Scene* pScene)
{
    auto* esp_scene = (Application::Canvas::CanvasForm*)pScene;

    if (BrokeProtocol::get_manager()->host != nullptr)
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

        const auto width = local_camera->worldCamera->get_pixelWidth();
        const auto height = local_camera->worldCamera->get_pixelHeight();

        UINT element_index = 0;

        float min_target_distance = 99999.f;

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

                auto distance = sqrt(pow(point_top.x, 2) + pow(point_top.y, 2));
                if (distance <= 300 && distance < min_target_distance)
                {
                    aim_target = player->rotationT;
                    min_target_distance = distance;
                    esp_box->set_color(0.5f, 0, 0);
                }
                else
                {
                    esp_box->set_color(0, 0.8f, 0);
                }
            }
        }

        for (; element_index < elements_size; element_index++)
        {
            auto* esp_box = (Application::Canvas::Rectangle*)esp_scene->element_at(element_index);
            esp_box->render = false;
        }

        if (min_target_distance == 99999.f)
        {
            aim_target = nullptr;
        }
    }
}

GBHRC::Context* GBHRC::Context::instance()
{
	static auto* gbhrc_context = new Context{};
	return gbhrc_context;
}

void GBHRC::Context::static_draw_callback(Application::Render::Scene* pScene)
{
    auto* context = GBHRC::Context::instance();
    context->draw_esp(pScene);
}
