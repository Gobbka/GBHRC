#pragma once
#include <string>

namespace GBHRC
{
	class Config
	{
	public:
		// public flags

		bool esp_active        = true;
		bool esp_draw_name     = true;
		bool esp_health_active = true;
		bool esp_draw_gun_name = true;
		bool aim_assist        = true;
		bool no_recoil         = true;
		bool fly_active		   = true;
		bool inf_inventory     = true;

		float draw_distance = 300.f;
		float fov_size      = 300.f;

		//

		std::string filename;
	public:
		void load(char*filename);
		void save();
	};
}
