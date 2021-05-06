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
			Render::Resolution resolution;
		public:
			// public variables
			void(__stdcall* render_callback)(Scene* self,Render::Engine*engine) = nullptr;
			bool hidden = false;
		public:
			// public void's

			void update(Render::Engine* pEngine);
			void render(Render::Engine*pEngine);

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
			IRenderObject* element_at(UINT index);

		public:
			~Scene();
		};
	}
}
