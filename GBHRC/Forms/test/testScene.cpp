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
	
	form->initialize_components(pEngine);
}

void test_scene_draw(Application::Render::DrawEvent* event)
{
	
    auto pos = Application::point_to_center(Application::Render::Position{ 0,0 });
	
    auto*engine = event->engine;

    engine->get_batch()->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr,engine->get_mask()->get_discardState());

    VisbyRoundCFFont->DrawString(
        engine->get_batch(),
        "NUMB DIGGER DUMB NIGGER",
        DirectX::XMFLOAT2(
            pos.x-70,
            pos.y
        ),
        DirectX::Colors::Red,
        0.0f,
        DirectX::XMFLOAT2(0.0f, 0.0f),
        1
    );
	
    engine->get_batch()->End();

    engine->get_mask()->unset_mask();
}
