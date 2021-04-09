#include "MenuMain.h"
#include "../../Application/UI/Panel/Panel.h"

Application::UI::Panel* background_panel = new Application::UI::Panel(Application::Render::Position{ 0,0,200,200 }, FLOAT_COLORS_BLACK);

void MainMenuMarkup(Application::Form* form,Application::Render::Engine*pEngine)
{
	form->add_markup_elements(
		1,
		background_panel
	);

	form->update_markup(pEngine);
}
