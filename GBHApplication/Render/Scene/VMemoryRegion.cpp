#include "VMemoryRegion.h"

Application::Render::VMemoryRegion::VMemoryRegion(GVertex::Vertex* pointer, UINT size,UINT offset)
{
	this->initialize(pointer, size, offset);
}

Application::Render::VMemoryRegion::VMemoryRegion()
{
	this->pointer = nullptr;
	this->size = this->offset = 0x0;
}

void Application::Render::VMemoryRegion::initialize(GVertex::Vertex* pointer, UINT size, UINT offset)
{
	this->pointer = pointer;
	this->size = size;
	this->offset = offset;
}

GVertex::Vertex* Application::Render::VMemoryRegion::operator[](UINT index) const
{
	return &this->pointer[index];
}

GVertex::Vertex* Application::Render::VMemoryRegion::get_pointer() const
{
	return this->pointer + this->offset;
}
