#include "MenuMain.h"

#include "../../resource.h"
#include "Render/Engine/Engine.h"
#include "Form/Interactive/elements/Panel/Panel.h"
#include "Form/Interactive/elements/Checkbox/Checkbox.h"
#include "Form/Interactive/elements/Label/Label.h"
#include "Form/Interactive/elements/Button/Button.h"
#include "../../CheatApi/GBHRC/gbhrc.h"


Application::UI::Panel* background_panel = new Application::UI::Panel({ 0,0 }, { 400, 500 }, { FLOAT_COLORS_BLACK });
Application::UI::Panel* topbar_panel = new Application::UI::Panel({ 0,0 }, { 400, 30 }, { FLOAT_COLORS_GREEN });
Application::UI::Checkbox* aim_checkbox = new Application::UI::Checkbox({ 20,-50 }, { 20,20 }, { FLOAT_COLORS_GRAY });
Application::UI::Checkbox* esp_checkbox = new Application::UI::Checkbox({ 20,-90 }, { 20,20 }, { FLOAT_COLORS_GRAY });
Application::UI::Checkbox* jump_checkbox = new Application::UI::Checkbox({ 20,-130 }, { 20,20 }, { FLOAT_COLORS_GRAY });
Application::UI::Checkbox* car_sh_checkbox = new Application::UI::Checkbox({ 20,-170 }, { 20,20 }, { FLOAT_COLORS_GRAY });


extern HMODULE DllInst;

void MainMenuMarkup(Application::InteractiveForm* form,Application::Render::Engine*pEngine)
{

	auto* esp_font = pEngine->create_font(
		(void*)LoadResource(DllInst, FindResourceW(DllInst, MAKEINTRESOURCE(IDR_VISBY_ROUND), L"SPRITEFONT")),
		0x6608
	);
	
	auto* esp_button = new Application::UI::Button({ 0,-30 }, { 400/3,50 }, { FLOAT_COLORS_GRAY },esp_font, "ESP");
	auto* aim_button = new Application::UI::Button({ 400/3,-30 }, { 400/3,50 }, { FLOAT_COLORS_GRAY },esp_font, "AIM");
	auto* misc_button = new Application::UI::Button({ 2*400/3,-30 }, { 400/3,50 }, { FLOAT_COLORS_GRAY },esp_font, "MISC");

	auto* esp_inner = new Application::UI::Panel{ {0,-80},{400,420},{FLOAT_COLORS_BLACK} };
	auto* aim_inner = new Application::UI::Panel{ {0,-80},{400,420},{FLOAT_COLORS_BLACK} };
	auto* misc_inner = new Application::UI::Panel{ {0,-80},{400,420},{FLOAT_COLORS_BLACK} };
	
	form
		->add_element(background_panel)
	;
	
	background_panel
		->add_element(aim_checkbox)
		->add_element(jump_checkbox)
		->add_element(car_sh_checkbox)
		->add_element(esp_button)
		->add_element(aim_button)
		->add_element(misc_button)
		// inners
		->add_element(
			esp_inner->add_element(esp_checkbox)//->add_element(new Application::UI::Label{ {60,-85},"ESP ACTIVE",esp_font,{FLOAT_COLORS_WHITE} })
		)
		->add_element(aim_inner)
		->add_element(misc_inner)
		->add_element(
			topbar_panel->add_element(new Application::UI::Label{ {0,0},"GBHRC",esp_font,{FLOAT_COLORS_WHITE},{400,30} })
		)
		->add_element(new Application::UI::Label{ {60,-45},"AIM ACTIVE",esp_font,{FLOAT_COLORS_WHITE} })
		->add_element(new Application::UI::Label{ {60,-125},"FLY",esp_font,{FLOAT_COLORS_WHITE} })
		->add_element(new Application::UI::Label{ {60,-165},"CAR SPEED",esp_font,{FLOAT_COLORS_WHITE} })
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
}
