#pragma once
#include <vector>
#include <functional>

#include "IRenderObject.h"
#include "../d3d/Vertex.h"
#include "../Render.h"

namespace Application
{
	namespace Render
	{
		class Engine;
		
		class Scene
		{
		private:
			GVertex::VertexBuffer* pVBuffer;
			std::vector<Render::IRenderObject*> pElements;
		protected:
			Render::Resolution screen_resolution;

			virtual void draw_element(Render::IRenderObject* obj,Render::DrawEvent*event)=0;
		public:
			// public variables
			void(__stdcall* render_callback)(Render::DrawEvent*event) = nullptr;
			bool hidden = false;
		public:
			// public void's

			void update(Render::Engine* pEngine);
			void render(Render::DrawEvent*event);

			void foreach(std::function<void(IRenderObject*)> const& nigger);
			UINT total_size();
		protected:
			void alloc_vbuffer(Render::Engine* pEngine);
			void add_render_object(IRenderObject* object);

		public:
			// public setters
			
			void set_resolution(Resolution resolution);
		public:
			// public getters

			UINT elements_length() const;
			GVertex::Vertex* get_ptr() const;
			GVertex::VertexBuffer* get_vbuffer();
			IRenderObject* element_at(UINT index);

			Resolution get_screen_resolution() const;

		protected:
			~Scene();
		};
	}
}
