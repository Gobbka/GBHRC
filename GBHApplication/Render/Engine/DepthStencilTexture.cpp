#include "DepthStencilTexture.h"
#include "Engine.h"

void Application::Render::DepthStencilTexture::create()
{
	_engine->pDevice->CreateTexture2D(&_texture_desc, nullptr, &_texture2D);
}
