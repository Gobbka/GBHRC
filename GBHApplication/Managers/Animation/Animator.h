#pragma once
#include <functional>
#include <vector>
#include <Windows.h>

namespace Application
{
	struct Animation
	{
		std::function<void(void* p_value,uint32_t step)> handler;
		void* p_value;
		uint32_t step;

		
	};
	
	class Animator
	{
		std::vector<Animation> animations;
		bool playing = false;
		HANDLE thread;

		static void handle_animations(Animator*animator);
	public:
		void start();
		void end();

	};
}
