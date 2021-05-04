#pragma once
#include <vector>

#include "InteractiveElement.h"
#include "../../../../Render/Scene/IRenderObject.h"

namespace Application
{
	namespace UI
	{
		
		class Parent : public InteractiveElement
		{
		private:
			std::vector<InteractiveElement*> elements;
		public:
			void __draw(ID3D11DeviceContext* p_context, ID3D11Device* pDevice) override;
			void set_pos(float x, float y) override;
			void set_color(float r, float g, float b) override;
			bool point_belongs(POINT point) override;
			UINT size() override;
			void move_by(float x, float y) override;
		};
	}
}
