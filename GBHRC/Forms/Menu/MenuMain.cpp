#pragma region includes

#include "MenuMain.h"

#include "FloatColors.h"
#include "../../resource.h"
#include "Render/Engine/Engine.h"
#include "Form/Interactive/elements/Panel/Panel.h"
#include "Form/Interactive/elements/Checkbox/Checkbox.h"
#include "Form/Interactive/elements/Label/Label.h"
#include "Form/Interactive/elements/Button/Button.h"
#include "Form/Interactive/elements/ItemList/ItemList.h"
#include "../../CheatApi/GBHRC/gbhrc.h"

#pragma endregion

#pragma region elements

Application::UI::Panel* background_panel = new Application::UI::Panel({ 0,0 }, { 400, 500 }, { FLOAT_COLORS_BLACK });
Application::UI::Panel* topbar_panel = new Application::UI::Panel({ 0,0 }, { 400, 30 }, { FLOAT_COLORS_GREEN });


auto* esp_inner = new Application::UI::Panel{ {0,-80},{400,420},{FLOAT_COLORS_BLACK} };
// ELEMENTS
auto* esp_checkbox = new Application::UI::Checkbox({ 20,-10 }, { 20,20 }, { FLOAT_COLORS_GRAY });
auto* name_checkbox = new Application::UI::Checkbox({ 20,-50 }, { 20,20 }, { FLOAT_COLORS_GRAY });


auto* aim_inner = new Application::UI::Panel{ {0,-80},{400,420},{FLOAT_COLORS_BLACK} };
// ELEMENTS
auto* aim_checkbox = new Application::UI::Checkbox({ 20,-30 }, { 20,20 }, { FLOAT_COLORS_GRAY });


auto* misc_inner = new Application::UI::Panel{ {0,-80},{400,420},{FLOAT_COLORS_BLACK} };
// ELEMENTS
auto* jump_checkbox = new Application::UI::Checkbox({ 20,-10 }, { 20,20 }, { FLOAT_COLORS_GRAY });
auto* car_sh_checkbox = new Application::UI::Checkbox({ 20,-50 }, { 20,20 }, { FLOAT_COLORS_GRAY });
auto* no_recoil_checkbox = new Application::UI::Checkbox({ 20,-90 }, { 20,20 }, { FLOAT_COLORS_GRAY });


#pragma endregion 

extern HMODULE DllInst;
extern DirectX::SpriteFont* VisbyRoundCFFont;

void MainMenuMarkup(Application::InteractiveForm* form,Application::Render::Engine*pEngine)
{
	auto* esp_button = new Application::UI::Button({ 0,-30 }, { 400/3,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "ESP");
	auto* aim_button = new Application::UI::Button({ 400/3,-30 }, { 400/3,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "AIM");
	auto* misc_button = new Application::UI::Button({ 2*400/3,-30 }, { 400/3+1,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "MISC");
	
	auto* items_list = new Application::UI::ItemList({ 0,400 }, { 500,325 }, { FLOAT_COLORS_BLACK });
	
	auto test_button = (new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "1NIGGER_BUTTON"));
	test_button->unique_id = 3;
	test_button->set_margin(5, 5);
	
	items_list
		->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "TEST_BUTTON"))
		->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
		->add_element(test_button)
		->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
		->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
		->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
		->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
		->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
		->add_element(new Application::UI::Button({ 0,0 }, { 0,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
	;
	
	form
		->add_element(background_panel)

		->add_element(items_list)
	;
	background_panel->styles.overflow = Application::UI::VISIBLE_STATE_HIDDEN;
	//topbar_panel->styles.overflow = Application::UI::VISIBLE_STATE_HIDDEN;
	//
	//background_panel
	//	->add_element(aim_checkbox)
	//	//->add_element(new Application::UI::Button({ -50,10 }, { 250,50 }, { COLOR_FROM_RGB(32,32,32) }, VisbyRoundCFFont, "NIGGER_BUTTON"))
	//	//->add_element(new Application::UI::Label{ {60,-10},"AIM ACTIVE",VisbyRoundCFFont,{FLOAT_COLORS_WHITE} })
	//
	//;
	
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
			->add_element(new Application::UI::Label{ {60,-10},"FLY",VisbyRoundCFFont,{FLOAT_COLORS_WHITE} })
			->add_element(new Application::UI::Label{ {60,-50},"CAR SPEED",VisbyRoundCFFont,{FLOAT_COLORS_WHITE} })
			->add_element(new Application::UI::Label{ {60,-90},"NO RECOIL",VisbyRoundCFFont,{FLOAT_COLORS_WHITE} })
			,false
		)
	;

	form->initialize_components(pEngine);
	// ; paste ur initialize code below
	
	{
		auto resolut = background_panel->get_resolution();
		background_panel->move_by( -200, resolut.height/2);
	}

	aim_checkbox->onChange = [](Application::UI::UIElementEventArgs args)
	{
		GBHRC::Context::instance()->config->aim_assist = ((Application::UI::Checkbox*)args)->is_checked();
	};

	esp_checkbox->onChange = [](Application::UI::UIElementEventArgs args)
	{
		GBHRC::Context::instance()->set_esp( ((Application::UI::Checkbox*)args)->is_checked());
	};

	jump_checkbox->onChange = [](Application::UI::UIElementEventArgs args)
	{
		GBHRC::Context::instance()->config->fly_active = (((Application::UI::Checkbox*)args)->is_checked());
	};

	car_sh_checkbox->onChange = [](Application::UI::UIElementEventArgs args)
	{
		GBHRC::Context::instance()->config->car_speed = (((Application::UI::Checkbox*)args)->is_checked());
	};

	no_recoil_checkbox->onChange = [](Application::UI::UIElementEventArgs args)
	{
		GBHRC::Context::instance()->config->no_recoil = (((Application::UI::Checkbox*)args)->is_checked());
	};

	using namespace Application::UI;
	
	esp_button->onClick = [](Application::UI::UIElementEventArgs args)
	{
		esp_inner->state.visible  = VISIBLE_STATE_VISIBLE;
		aim_inner->state.visible  = VISIBLE_STATE_HIDDEN;
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
