#pragma once
#include "../d3d/Vertex.h"
#include "../Events/EngineEvents.h"

namespace Application
{
	namespace Render
	{
		class Engine;

		class IRenderObject
		{
		protected:
			UINT __index;
			
		public:
			virtual ~IRenderObject() = default;
			virtual void draw(Render::DrawEvent*event)        PURE;
			virtual void set_pos(float x, float y)            PURE;
			virtual void set_color(float r, float g, float b) PURE;
			virtual bool point_belongs(POINT point) = 0;

			virtual UINT size() PURE;
			virtual void move_by(float x, float y) PURE;

			UINT get_index() CONST
			{
				return this->__index;
			}
			
			void set_index(UINT index)
			{
				this->__index = index;
			}
		};
	}
}
