#pragma once
#include "../../../../Render/Render.h"
#include "../../../../Render/Scene/IRenderObject.h"

namespace Application
{
	namespace Canvas {

		class CanvasElement : public Render::IRenderObject
		{
		public:
			virtual ~CanvasElement() = default;
		protected:
			UINT index PURE;

			Application::Render::CanvasScene* pcanvas = nullptr;
			Render::Position position{ 0,0 };
			virtual void init() PURE;

		public:
			UINT get_index() CONST
			{
				return this->index;
			}

			void set_index(UINT index)
			{
				this->index = index;
			}
			
			virtual UINT size() PURE;

			bool render = true;

			Render::Position get_position() const;

			void move_by(float x, float y) override = 0;

			void initialize(Render::CanvasScene* pForm);

			GVertex::Vertex* get_ptr();
		};
	}
}
