#pragma once
#include <vector>
#include <functional>


#include "D3D11Canvas.h"
#include "IRenderObject.h"

#include "../Render.h"

namespace Application
{
	namespace Render
	{
		class Engine;
		
		class Scene : public D3D11Canvas
		{
		private:

			std::vector<Render::IRenderObject*> pElements;
		protected:

			virtual void draw_element(Render::IRenderObject* obj,Render::DrawEvent*event) PURE;
		public:
			// public variables
			void(__cdecl* render_callback)(Render::DrawEvent*event)     = nullptr;
			void(__cdecl* pre_render_callback)(Render::DrawEvent*event) = nullptr;
			bool hidden = false;
		public:
			// public void's

			void update(Render::Engine* pEngine);
			void render(Render::DrawEvent*event);

			void foreach(std::function<void(IRenderObject*)> const& callback);
		protected:
			void alloc_vbuffer(Render::Engine* pEngine);
			void add_render_object(IRenderObject* object);

			void set_indexes();
		public:
			// public getters

			size_t elements_length() const;

			IRenderObject* element_at(UINT index);

			UINT total_size();
		};
	}
}
