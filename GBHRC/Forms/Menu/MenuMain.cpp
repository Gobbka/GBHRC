#include "MenuMain.h"

#include "../../resource.h"
#include "Render/Engine/Engine.h"
#include "Form/Interactive/elements/Panel/Panel.h"
#include "Form/Interactive/elements/Checkbox/Checkbox.h"
#include "Form/Interactive/elements/Label/Label.h"


Application::UI::Panel* background_panel = new Application::UI::Panel({ 0,0 }, { 400, 600 }, { FLOAT_COLORS_BLACK });
Application::UI::Panel* topbar_panel = new Application::UI::Panel({ 0,0 }, { 400, 30 }, { FLOAT_COLORS_GREEN });
Application::UI::Checkbox* checkbox = new Application::UI::Checkbox({ 50,-50 }, { 20,20 }, { FLOAT_COLORS_GRAY });

extern HMODULE DllInst;

void MainMenuMarkup(Application::InteractiveForm* form,Application::Render::Engine*pEngine)
{

	auto* esp_font = pEngine->create_font(
		(void*)LoadResource(DllInst, FindResourceW(DllInst, MAKEINTRESOURCE(IDR_VISBY_ROUND), L"SPRITEFONT")),
		0x6608
	);

	form
		->add_element(background_panel);

	background_panel
		->add_element(checkbox)
		->add_element(
			topbar_panel->add_element(new Application::UI::Label{ {0,0},"GBHRC",esp_font,{FLOAT_COLORS_WHITE},{400,30} })
		);

	form->update_markup(pEngine);

	
	{
		auto resolut = background_panel->get_resolution();
		background_panel->move_by( -200, resolut.height / 2);
	}

	topbar_panel->onMouseDown = [](Application::UI::UIElementEventArgs args)
	{
		DEBUG_LOG("NIGGER");
		//args->get_form()->drag_move(args->get_parent());
	};
}
