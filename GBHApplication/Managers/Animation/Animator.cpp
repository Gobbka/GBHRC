#include "Animator.h"


void Application::Animator::handle_animations(Animator* animator)
{
	while(animator->playing)
	{

		Sleep(10);
	}

	ExitThread(0);
}

void Application::Animator::start()
{
	this->playing = true;
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)handle_animations, this, NULL, nullptr);
}

void Application::Animator::end()
{
	this->playing = false;
}
