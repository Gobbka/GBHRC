#pragma once
#include "../d3d/Vertex.h"
namespace Application
{
	namespace Render
	{
		class VMemoryRegion
		{
		private:
			GVertex::Vertex* pointer;
			UINT size;
			UINT index;
			UINT offset;
		public:
			VMemoryRegion(GVertex::Vertex*pointer,UINT size,UINT offset=0);
			VMemoryRegion();

			void initialize(GVertex::Vertex* pointer, UINT size, UINT offset = 0);

			GVertex::Vertex* operator[](UINT index) const;

			GVertex::Vertex* get_pointer() const;
		};
	}
}

