#pragma once
#include <vector>

#include "config/Config.h"
#include "../BrokeProtocol/BrokeProtocol.h"
#include "../../../GBHApplication/configuration/drawconf.h"
#include "../../../GBHApplication/Render/Render.h"


namespace Application {
	namespace Canvas {
		class Rectangle;
	}
}

namespace Application {
	namespace Render {
		struct D3D11DrawEvent;
		class Engine;
		class CanvasScene;
	}
}

namespace GBHRC
{

	struct EspBox
	{
		Application::Render::Position box_position;
		Application::Render::Resolution box_resolution;
		
		Application::Canvas::Rectangle* box;
		Application::Canvas::Rectangle* max_health_box;
		Application::Canvas::Rectangle* health_box;

		void disable();
	};

	class EspPlayer
	{
	public:
		EspBox* box;
		BrokeProtocol::Players::ShPlayer* player;
		float map_distance;
		float display_distance;


		bool apply_box(Matrix4X4* view_matrix, Matrix4X4* projection_matrix, Application::Render::Resolution camera_resolution);
		
		EspPlayer(EspBox*box);
	};
	
	class Context
	{
	private:
		static void receive_lua_thread();
		
		HMODULE DllInst;
		UnityEngine::Transform* aim_target = nullptr;
		
		Context();

		void render_callback(Application::Render::DrawEvent*event);
		void draw_player(Application::Render::DrawEvent* event,Application::Render::Resolution camera_resolution,EspPlayer*player);
		bool is_aim_target(EspPlayer* old_player, EspPlayer* new_player) const;

		std::vector<EspBox*> esp_boxes;
		Application::Render::CanvasScene* esp_scene;
		std::vector<wchar_t*> friend_list;
	public:
		void set_speed_hack(bool enable);
		void set_fly(bool enable);
		
		void set_esp(bool status);
		bool is_friend(wchar_t* nickname);

		void add_friend(wchar_t* nickname);
		void remove_friend(wchar_t* nickname);
		
		Config* config;

		
		bool aim_active = false;

		void implement(HMODULE DllInst);
		static Context* instance();

		void make_esp_boxes();
		void set_esp_scene(Application::Render::CanvasScene*form);

		static void static_draw_callback(Application::Render::DrawEvent*event);
		void life_cycle();
	};

}

