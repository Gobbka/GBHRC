#pragma once
#include <vector>
#include <functional>


#include "D3D11Canvas.h"
#include "IRenderObject.h"

#include "../../configuration/drawconf.h"
#include "../../Form/Canvas/elements/IElement/CanvasElement.h"
#include "../../Types/IForm.h"

namespace Application
{
	namespace Render
	{
		class Engine;
		
		class CanvasScene : public IScene
		{
		private:

			D3D11Canvas _canvas;
			
			std::vector<Canvas::CanvasElement*> elements;

		protected:
			virtual void render_components(Render::DrawEvent*event);
			static void draw_element(Canvas::CanvasElement* obj, Render::DrawEvent*event);
		public:
			virtual ~CanvasScene() = default;
			// public variables
			void(__cdecl* render_callback)(Render::DrawEvent*event)     = nullptr;
			void(__cdecl* pre_render_callback)(Render::DrawEvent*event) = nullptr;
		public:
			// public void's

			void update() override;
			void render(Render::DrawEvent*event) override;

			void foreach(std::function<void(Canvas::CanvasElement*)> const& callback);
			void add_canvas_element(Canvas::CanvasElement* object);

		private:
			UINT count_size();
		protected:
			void set_indexes();
		public:
			// public getters

			D3D11Canvas* canvas();

			size_t elements_length() const;

			Canvas::CanvasElement* element_at(UINT index);

			CanvasScene(Render::Engine* pEngine);
		};
	}
}
