#include "MenuMain.h"
#include "Form/Interactive/elements/Panel/Panel.h"
#include "Form/Interactive/elements/Checkbox/Checkbox.h"

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

void MainMenuMarkup(Application::InteractiveForm* form,Application::Render::Engine*pEngine)
{
	form->add_markup_elements(
		2,
		background_panel,
		checkbox
	);

	form->update_markup(pEngine);

	background_panel->onMouseEnter = panel_hover;
	background_panel->onMouseLeave = panel_leave;
}
