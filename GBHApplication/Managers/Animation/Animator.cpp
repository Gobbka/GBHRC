#include "Animator.h"

#include "../../../GBHRC/includes/logger.h"


Application::Animation::Animation(void* p_value, uint32_t during, AnimationHandler handler)
{
	this->during = during;
	this->p_value = p_value;
	this->handler = handler;
	this->step = 0;
}

bool Application::Animation::play_step()
{
	if(this->during > 0)
	{
		DEBUG_LOG("ANIMATION: "<<this->during);
		this->during -= 10;
		return true;
	}
	
	return false;
}

void Application::Animator::handle_animations(Animator* animator)
{
	while(animator->playing)
	{
		for(int i = 0;i<animator->animations.size();i++)
		{
			auto anim = animator->animations[i];
			if(!anim.play_step())
			{
				// remove animation from anim list;
				animator->remove_anim(i);
			}
		}
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

void Application::Animator::remove_anim(UINT index)
{
	this->animations.erase(this->animations.begin() + index);
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
