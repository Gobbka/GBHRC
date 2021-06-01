#pragma once
#include <vector>
#include <functional>


#include "D3D11Canvas.h"
#include "IRenderObject.h"

#include "../Render.h"
#include "../../configuration/drawconf.h"
#include "../../Form/Canvas/elements/IElement/CanvasElement.h"

namespace Application
{
	namespace Render
	{
		class Engine;
		
		class CanvasScene : public D3D11Canvas
		{
		private:

			std::vector<Canvas::CanvasElement*> pElements;
			bool components_initialized = false;

		protected:
			virtual void render_components(Render::DrawEvent*event);
			static void draw_element(Canvas::CanvasElement* obj, Render::DrawEvent*event);
		public:
			// public variables
			void(__cdecl* render_callback)(Render::DrawEvent*event)     = nullptr;
			void(__cdecl* pre_render_callback)(Render::DrawEvent*event) = nullptr;
			bool hidden = false;
		public:
			// public void's
			virtual void initialize_components(Application::Render::Engine* pEngine);

			void update(Render::Engine* pEngine);
			void render(Render::DrawEvent*event);

			void foreach(std::function<void(Canvas::CanvasElement*)> const& callback);
			void add_element(Canvas::CanvasElement* object);

		private:
			UINT count_size();
		protected:
			void set_indexes();
		public:
			// public getters

			size_t elements_length() const;

			Canvas::CanvasElement* element_at(UINT index);

		};
	}
}
