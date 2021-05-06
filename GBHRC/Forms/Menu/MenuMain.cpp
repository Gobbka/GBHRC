#include "MenuMain.h"

#include "../../resource.h"
#include "Render/Engine/Engine.h"
#include "Form/Interactive/elements/Panel/Panel.h"
#include "Form/Interactive/elements/Checkbox/Checkbox.h"
#include "Form/Interactive/elements/Label/Label.h"


Application::UI::Panel* background_panel = new Application::UI::Panel({ 0,0 }, { 200, 200 }, { FLOAT_COLORS_BLACK });
Application::UI::Checkbox* checkbox = new Application::UI::Checkbox({ 5,-5 }, { 20,20 }, { FLOAT_COLORS_GRAY });

void panel_hover(Application::UI::UIElementEventArgs args)
{
	args->set_color(FLOAT_COLORS_GREEN);
}

void panel_leave(Application::UI::UIElementEventArgs args)
{
	args->set_color(FLOAT_COLORS_BLACK);
}

extern HMODULE DllInst;

void MainMenuMarkup(Application::InteractiveForm* form,Application::Render::Engine*pEngine)
{

	auto* nigger = LoadResource(DllInst, FindResourceW(DllInst, MAKEINTRESOURCEW(IDR_VISBY_ROUND), L"SPRITEFONT"));
	if (nigger == nullptr)
	{
		DEBUG_LOG("CANNOT CREATE FONT");
		return;
	}
	DirectX::SpriteFont* esp_font = new DirectX::SpriteFont(pEngine->pDevice, (uint8_t*)nigger, 0x6608);

	esp_font->SetDefaultCharacter('?');
	
	form
		->add_element(background_panel)
		->add_element(new Application::UI::Label{{5.f,5.f},"GBHRC::DLL",esp_font, {FLOAT_COLORS_GREEN} });
	// background_panel->add_element(checkbox);

	form->update_markup(pEngine);

	background_panel->onMouseEnter = panel_hover;
	background_panel->onMouseLeave = panel_leave;
	background_panel->onMouseDown = [](Application::UI::UIElementEventArgs args)
	{
		args->get_form()->drag_move(args);
	};
}
