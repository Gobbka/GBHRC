#include "Animator.h"


Application::Animation::Animation(void* p_value, uint32_t during, AnimationHandler handler)
{
	this->during = during;
	this->p_value = p_value;
	this->handler = handler;
	this->step = 0;
}

void Application::Animator::handle_animations(Animator* animator)
{
	while(animator->playing)
	{

		Sleep(10);
	}

	ExitThread(0);
}

void Application::Animator::def_anim_float(void* flt, uint32_t step)
{
	
}

void Application::Animator::add_anim(float* value, UINT during, Animation::AnimationHandler anim)
{
	this->animations.push_back(Animation(value,during,anim));
}

void Application::Animator::start()
{
	if(this->playing==false)
	{
		this->playing = true;
		CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)handle_animations, this, NULL, nullptr);
	}
}

void Application::Animator::end()
{
	this->playing = false;
}
