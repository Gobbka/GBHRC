#pragma once
#include "../configuration/drawconf.h"

namespace Application
{
	class  IScene
	{
	private:
		bool _hidden = false;
	public:
		void hide() { _hidden = true; }
		void show() { _hidden = false; }
		bool hidden() const { return _hidden; }
		
		virtual void update() = 0;
		virtual void render(Render::DrawEvent* event)   = 0;
	};
}
