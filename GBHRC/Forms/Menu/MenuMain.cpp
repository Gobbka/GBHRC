#include "MenuMain.h"

#include "../../resource.h"
#include "Render/Engine/Engine.h"
#include "Form/Interactive/elements/Panel/Panel.h"
#include "Form/Interactive/elements/Checkbox/Checkbox.h"
#include "Form/Interactive/elements/Label/Label.h"


Application::UI::Panel* background_panel = new Application::UI::Panel({ 0,0 }, { 400, 600 }, { FLOAT_COLORS_BLACK });
Application::UI::Panel* topbar_panel = new Application::UI::Panel({ 0,0 }, { 400, 30 }, { FLOAT_COLORS_GREEN });
Application::UI::Checkbox* checkbox = new Application::UI::Checkbox({ 50,-50 }, { 20,20 }, { FLOAT_COLORS_RED });

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
		->add_element(background_panel);

	background_panel->add_element(checkbox);

	DEBUG_LOG("BACKPANEL SIZE: " << background_panel->size());

	form->update_markup(pEngine);
	
	{
		
		auto resolut = background_panel->get_resolution();
		DEBUG_LOG("PANEL:"<<std::dec<<resolut.width << " "<<resolut.height);
		background_panel->move_by( -200, resolut.height / 2);
	}

	background_panel->onMouseDown = [](Application::UI::UIElementEventArgs args)
	{
		args->get_form()->drag_move(args);
	};
}
