#include "testScene.h"


#include "FloatColors.h"
#include "Form/Canvas/elements/rectangle/rectangle.h"
#include "Render/Engine/Engine.h"

extern DirectX::SpriteFont* VisbyRoundCFFont;

void TestSceneMarkup(Application::Canvas::CanvasForm* form, Application::Render::Engine* pEngine)
{
    form
        ->add_element(new Application::Canvas::Rectangle{ {-500,500},{1000,1000},{FLOAT_COLORS_RED} })
	;
	
	form->update_markup(pEngine);
}

void test_scene_draw(Application::Render::DrawEvent* event)
{
    auto pos = Application::point_to_center(Application::Render::Position{ 0,0 });
	
    auto*engine = event->engine;

    engine->get_batch()->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, engine->get_mask()->get_applyMask());

    VisbyRoundCFFont->DrawString(
        engine->get_batch(),
        "NIGGER",
        DirectX::XMFLOAT2(
            pos.x,
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
