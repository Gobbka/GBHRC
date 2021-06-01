#pragma once
#include <functional>
#include <vector>
#include <Windows.h>

namespace Application
{
	struct Animation
	{
	public:
		typedef std::function<void(void* p_value, uint32_t step)> AnimationHandler;
	private:
		
		AnimationHandler handler;
		void* p_value;
		uint32_t step;
		uint32_t during;
	public:
		Animation(void* p_value, uint32_t during, AnimationHandler handler);


		bool play_step();
	};
	
	class Animator
	{
		std::vector<Animation> animations;
		bool playing = false;
		HANDLE thread;

		static void handle_animations(Animator*animator);
		static void def_anim_float(void* flt, uint32_t step);
	public:
		void add_anim(float* value, UINT during, Animation::AnimationHandler = def_anim_float);
		
		void start();
		void end();

	};
}
