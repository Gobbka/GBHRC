#include "Animator.h"

#include <utility>

#include "../../../GBHRC/includes/logger.h"


Application::Animation::Animation(float from_value, float to_value, UINT during, Animation::tSetFunction set_function, Animation::tAnimFunc anim_handle)
{
	_end_time = during;
	_during = 0;
	_value = from_value;
	_step = (to_value - from_value) / (float)during;

	_set_function = std::move(set_function);
	_anim_func = anim_handle;
}

bool Application::Animation::play_step(int delta_time)
{
	if(_during < _end_time)
	{
		_value += _step * _anim_func(_during) * delta_time;
		
		_set_function(_value);
		
		_during += delta_time;
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
			if(!anim->play_step(10))
			{
				// remove animation from anim list;
				animator->remove_anim(i);
			}
		}
		Sleep(10);
	}

	ExitThread(0);
}

Application::Animator::Animator()
{
	_thread = nullptr;
}

Application::Animator::~Animator()
{
}

void Application::Animator::add_animation(Animation* animation)
{
	_animations.push_back(animation);
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
