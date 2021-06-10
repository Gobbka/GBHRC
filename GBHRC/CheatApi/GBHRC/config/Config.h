#pragma once
#include <string>

namespace GBHRC
{
	class Config
	{
	public:
		// public flags

		bool esp_active        = false;
		bool esp_draw_name     = false;
		bool esp_health_active = false;
		bool esp_draw_gun_name = false;
		bool aim_assist        = false;
		bool no_recoil         = false;
		bool fly_active		   = false;
		bool inf_inventory     = false;
		bool car_speed         = false;

		float draw_distance = 300.f;
		float fov_size      = 150.f;

		//

		std::string filename;
	public:
		
		void load(char*filename);
		void save();
	};
}
