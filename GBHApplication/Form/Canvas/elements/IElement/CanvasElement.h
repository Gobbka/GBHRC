#pragma once
#include "../../../../Render/Render.h"
#include "../../../../Render/Scene/IRenderObject.h"

namespace Application
{
	namespace Canvas {
		class CanvasForm;

		class CanvasElement : public Render::IRenderObject
		{
		public:
			virtual ~CanvasElement() = default;
		protected:
			Application::Canvas::CanvasForm* pcanvas = nullptr;
			Render::Position position{ 0,0 };
		public:
			bool hovered = false;

			Render::Position get_position() const;

			void move_by(float x, float y) override = 0;

			virtual void init(CanvasForm* pForm) = 0;

			GVertex::Vertex* get_ptr() const;
		};
	}
}
