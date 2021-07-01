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
	while(animator->_playing)
	{
		for(int i = 0;i<animator->_animations.size();i++)
		{
			auto* anim = animator->_animations[i];
			if(!anim->play_step())
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

Application::Animator::Animator()
{
	_thread = nullptr;
}

Application::Animator::~Animator()
{
}

void Application::Animator::add_anim(float* value, UINT during, Animation::AnimationHandler anim)
{
	_animations.push_back(new Animation(value,during,anim));
}

void Application::Animator::remove_anim(UINT index)
{
	delete _animations[index];
	_animations.erase(_animations.begin() + index);
}

void Application::Animator::start()
{
	if(_playing==false)
	{
		_playing = true;
		CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)handle_animations, this, NULL, nullptr);
	}
}

void Application::Animator::end()
{
	_playing = false;
}
