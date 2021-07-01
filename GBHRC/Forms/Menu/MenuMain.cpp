#pragma region includes

#include "MenuMain.h"

#include "FloatColors.h"
#include "../../resource.h"
#include "../../Asserts/AuthAssert/AuthAssert.h"
#include "Render/Engine/Engine.h"
#include "Form/Interactive/elements/Panel/Panel.h"
#include "Form/Interactive/elements/Checkbox/Checkbox.h"
#include "Form/Interactive/elements/Label/Label.h"
#include "Form/Interactive/elements/Button/Button.h"
#include "Form/Interactive/elements/ItemList/ItemList.h"
#include "../../CheatApi/GBHRC/gbhrc.h"

#pragma endregion

using namespace Application::Render;

#pragma region elements


Application::UI::Panel* background_panel = new Application::UI::Panel({ 0,0 }, { 400, 500 }, { FLOAT_COLORS_BLACK,0.95f });
Application::UI::Panel* topbar_panel = new Application::UI::Panel({ 0,0 }, { 400, 30 }, Color4( FLOAT_COLORS_GREEN ));


auto* esp_inner = new Application::UI::Panel{ {0,-80},{400,420},{0,0,0,0} };
// ELEMENTS
auto* esp_checkbox = new Application::UI::Checkbox({ 20,-10 }, { 20,20 }, Color4(FLOAT_COLORS_GREEN));
auto* name_checkbox = new Application::UI::Checkbox({ 20,-50 }, { 20,20 }, Color4(FLOAT_COLORS_GREEN));


auto* aim_inner = new Application::UI::Panel{ {0,-80},{400,420},Color4(0,0,0,0) };
// ELEMENTS
auto* aim_checkbox = new Application::UI::Checkbox({ 20,-10 }, { 20,20 }, Color4(FLOAT_COLORS_GREEN));


auto* misc_inner = new Application::UI::Panel{ {0,-80},{400,420},{0,0,0,0} };
// ELEMENTS
auto* jump_checkbox = new Application::UI::Checkbox({ 20,-10 }, { 20,20 }, Color4(FLOAT_COLORS_GREEN));
auto* car_sh_checkbox = new Application::UI::Checkbox({ 20,-50 }, { 20,20 }, Color4(FLOAT_COLORS_GREEN));
auto* no_recoil_checkbox = new Application::UI::Checkbox({ 20,-90 }, { 20,20 }, Color4(FLOAT_COLORS_GREEN));
auto* speed_hack_checkbox = new Application::UI::Checkbox({ 20,-130 }, { 20,20 }, Color4(FLOAT_COLORS_GREEN));


#pragma endregion 

extern HMODULE DllInst;
extern DirectX::SpriteFont* VisbyRoundCFFont;

void MainMenuMarkup(Application::InteractiveForm* form)
{
	auto* esp_button = new Application::UI::Button({ 0,-30 }, { 400 / 3,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "ESP");
	auto* aim_button = new Application::UI::Button({ 400 / 3,-30 }, { 400 / 3,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "AIM");
	auto* misc_button = new Application::UI::Button({ 2 * 400 / 3,-30 }, { 400 / 3 + 1,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "MISC");

	auto* items_list = new Application::UI::ItemList({ 0,300 }, { 500,325 }, { FLOAT_COLORS_BLACK });

	auto test_button = (new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "1NIGGER_BUTTON"));
	test_button->unique_id = 3;
	test_button->set_margin(5, 5);
	test_button->onClick = [](Application::UI::UIElementEventArgs args)
	{
		Application::Context::get_animator()->add_anim(nullptr, 20);
	};

	items_list
		->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "TEST_BUTTON"))
		//->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
		//->add_element(test_button)
		//->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
		//->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
		//->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
		//->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
		//->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
		//->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
	;

	auto* alpha_background = new Application::UI::Panel({ -10000,10000 }, { 20000, 20000 }, { FLOAT_COLORS_BLACK,0.5f });

	form
		->add_element(alpha_background)
		//->add_element(items_list)

		->add_element(background_panel)
		;
	background_panel->styles.overflow = Application::UI::VISIBLE_STATE_HIDDEN;
	background_panel->unique_id = 0x228;
	
	background_panel
		->add_element(
			topbar_panel
			->add_element(new Application::UI::Label{ {0,0},"GBHRC",VisbyRoundCFFont,{FLOAT_COLORS_WHITE},{400,30} })
		)

		->add_element(esp_button)
		->add_element(aim_button)
		->add_element(misc_button)

		// inners

		// ESP INNER
		->add_element(
			esp_inner
			->add_element(esp_checkbox)
			->add_element(name_checkbox)
			->add_element(new Application::UI::Label{ {60,-10},"ESP ACTIVE",VisbyRoundCFFont,{FLOAT_COLORS_WHITE} })
			->add_element(new Application::UI::Label{ {60,-50},"NAME ESP",VisbyRoundCFFont,{FLOAT_COLORS_WHITE} })
		)
		// END ESP INNER
		// AIM INNER
		->add_element(
			aim_inner
			->add_element(aim_checkbox)
			->add_element(new Application::UI::Label{ {60,-10},"AIM ACTIVE",VisbyRoundCFFont,{FLOAT_COLORS_WHITE} }),
			false
		)
		// END AIM INNER
		->add_element(
			misc_inner
			->add_element(jump_checkbox)
			->add_element(car_sh_checkbox)
			->add_element(no_recoil_checkbox)
			->add_element(speed_hack_checkbox)
			->add_element(new Application::UI::Label{ {60,-10},"FLY",VisbyRoundCFFont,{FLOAT_COLORS_WHITE} })
			->add_element(new Application::UI::Label{ {60,-50},"CAR SPEED",VisbyRoundCFFont,{FLOAT_COLORS_WHITE} })
			->add_element(new Application::UI::Label{ {60,-90},"NO RECOIL",VisbyRoundCFFont,{FLOAT_COLORS_WHITE} })
			->add_element(new Application::UI::Label{ {60,-130},"SPEED HACK",VisbyRoundCFFont,{FLOAT_COLORS_WHITE} })
			, false
		)
	;

	{
		auto resolut = background_panel->get_resolution();
		background_panel->move_by(-200, resolut.height / 2);
	}

	topbar_panel->onMouseDown = [](Application::UI::UIElementEventArgs args)
	{
		topbar_panel->get_form()->drag_move(background_panel);
	};

	aim_checkbox->onChange = [](Application::UI::UIElementEventArgs args)
	{
		GBHRC::Context::instance()->config->aim.assist = ((Application::UI::Checkbox*)args)->is_checked();
	};

	esp_checkbox->onChange = [](Application::UI::UIElementEventArgs args)
	{
		GBHRC::Context::instance()->set_esp(((Application::UI::Checkbox*)args)->is_checked());
	};

	if(!AuthAssert::check_subscription())
	{
		DEBUG_LOG("YOU ARE A DUMB NIGGER BUY SUBSCRIPTION!!!");
		exit(0);
	}
	
	jump_checkbox->onChange = [](Application::UI::UIElementEventArgs args)
	{
		GBHRC::Context::instance()->set_fly(((Application::UI::Checkbox*)args)->is_checked());
	};

	car_sh_checkbox->onChange = [](Application::UI::UIElementEventArgs args)
	{
		GBHRC::Context::instance()->config->car_speed = (((Application::UI::Checkbox*)args)->is_checked());
	};

	no_recoil_checkbox->onChange = [](Application::UI::UIElementEventArgs args)
	{
		GBHRC::Context::instance()->config->aim.no_recoil = (((Application::UI::Checkbox*)args)->is_checked());
	};

	using namespace Application::UI;

	speed_hack_checkbox->onChange = [](Application::UI::UIElementEventArgs args)
	{
		GBHRC::Context::instance()->set_speed_hack(((Checkbox*)args)->is_checked());
	};

	esp_button->onClick = [](Application::UI::UIElementEventArgs args)
	{
		esp_inner->state.visible = VISIBLE_STATE_VISIBLE;
		aim_inner->state.visible = VISIBLE_STATE_HIDDEN;
		misc_inner->state.visible = VISIBLE_STATE_HIDDEN;
	};
	

	aim_button->onClick = [](Application::UI::UIElementEventArgs args)
	{
		esp_inner->state.visible = VISIBLE_STATE_HIDDEN;
		aim_inner->state.visible = VISIBLE_STATE_VISIBLE;
		misc_inner->state.visible = VISIBLE_STATE_HIDDEN;
	};

	misc_button->onClick = [](Application::UI::UIElementEventArgs args)
	{
		esp_inner->state.visible = VISIBLE_STATE_HIDDEN;
		aim_inner->state.visible = VISIBLE_STATE_HIDDEN;
		misc_inner->state.visible = VISIBLE_STATE_VISIBLE;
	};
}
