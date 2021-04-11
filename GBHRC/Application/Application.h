#pragma once

#include "../includes/d3d.h"
#include "../includes/logger.h"
#include "../includes/win.h"

namespace Application
{
	namespace Render
	{
		struct Color
		{
			float r; float g; float b;
		};
		
		struct Resolution
		{
			UINT width;
			UINT height;
		};

		struct Position
		{
			float x; float y;
		};

		class Engine;
		class Scene;
	}

	namespace UI
	{
		class IElement;
		typedef IElement* UIElementEventArgs;
	}

	namespace Managers
	{
		class Rectangle;
	}

	class Form;

	void set_main_hwnd(HWND hwnd);

	void register_form(Form* form);
	void wnd_proc(UINT msg, WPARAM wParam, LPARAM lParam);

	POINT nigger();
}


#include "Render/d3d/Vertex.h"
#include "Render/d3d/ConstantBuffer.h"
#include "Render/d3d/szShadez.h"
#include "Render/Engine/Engine.h"
#include "Render/Scene/Scene.h"

#include "UI/IElement/IElement.h"

#include "Managers/RectangleManager.h"