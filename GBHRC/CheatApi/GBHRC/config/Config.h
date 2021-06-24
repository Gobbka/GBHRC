#pragma once
#include <string>

namespace GBHRC
{
	struct EspConfig
	{
		bool active = false;
		bool draw_name = true;
		bool draw_health = true;
		bool draw_gun_name = true;
	};

	struct AimConfig
	{
		bool assist = false;
		bool no_recoil = false;
		float draw_distance = 300.f;
		float fov_size = 150.f;
	};
	
	class Config
	{
	public:
		// public flags

		EspConfig esp;
		AimConfig aim;
		
		bool fly_active		   = false;
		bool inf_inventory     = false;
		bool car_speed         = false;
		//

		std::string filename;
	public:
		
		void load(char*filename);
		void save();
	};
}
