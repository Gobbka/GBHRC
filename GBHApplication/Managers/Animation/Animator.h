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
		volatile int during;
	public:
		Animation(void* p_value, uint32_t during, AnimationHandler handler);

		bool play_step();
	};
	
	class Animator
	{
		std::vector<Animation*> _animations;
		bool _playing = false;
		HANDLE _thread;

		static void handle_animations(Animator*animator);
		static void def_anim_float(void* flt, uint32_t step);
	public:
		Animator();
		~Animator();
		
		void add_anim(float* value, UINT during, Animation::AnimationHandler = def_anim_float);
		void remove_anim(UINT index);
		
		void start();
		void end();

	};
}
