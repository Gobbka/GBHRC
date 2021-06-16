#include "testScene.h"


#include "FloatColors.h"
#include "Form/Canvas/elements/rectangle/rectangle.h"
#include "Render/Engine/Engine.h"

extern DirectX::SpriteFont* VisbyRoundCFFont;

void TestSceneMarkup(Application::Render::CanvasScene* form, Application::Render::Engine* pEngine)
{
    form
        ->add_element(new Application::Canvas::Rectangle{ {-250,50},{800,200},{FLOAT_COLORS_GREEN} })
	;
	form->add_element(new Application::Canvas::Rectangle{ {-50,50},{200,200},{FLOAT_COLORS_RED} });
	
}

void test_scene_draw(Application::Render::D3D11DrawEvent* event)
{

}
