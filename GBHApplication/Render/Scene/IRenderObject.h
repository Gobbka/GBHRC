#pragma once
#include "../d3d/Vertex.h"

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
			virtual void __draw(Render::Engine*engine)=0;
			virtual void set_pos(float x, float y) = 0;
			virtual void set_color(float r, float g, float b) = 0;
			virtual bool point_belongs(POINT point) = 0;

			virtual UINT size() = 0;
			virtual void move_by(float x, float y) = 0;

			void set_index(UINT index)
			{
				this->__index = index;
			}
		};
	}
}
