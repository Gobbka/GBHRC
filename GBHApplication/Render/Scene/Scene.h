#pragma once

#include "../d3d/Vertex.h"
#include <vector>

#include "../../UI/IElement/IElement.h"

namespace Application
{
	namespace Render
	{
		class Scene
		{
		private:
			GVertex::VertexBuffer* pVBuffer;
		protected:
			std::vector<Application::UI::IElement*> pElements;
			Render::Resolution resolution;
		public:
			// public variables
			typedef void(__stdcall* tRenderCallback)(Scene*self);
			tRenderCallback render_callback = nullptr;
			bool hidden = false;
		public:
			// public void's
			void alloc_vbuffer(Render::Engine* pEngine);

			void update(ID3D11DeviceContext*pContext);
			void render(ID3D11DeviceContext* pContext);
		public:
			// public setters
			
			void set_resolution(Resolution resolution);
			void add_markup_elements(UINT count, Application::UI::IElement* elements...);
		public:
			// public getters
			
			GVertex::Vertex* get_ptr() const;
		public:
			~Scene();
		};
	}
}
