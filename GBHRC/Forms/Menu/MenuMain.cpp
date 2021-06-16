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


Application::UI::Panel* background_panel = new Application::UI::Panel({ 0,0 }, { 400, 500 }, { FLOAT_COLORS_BLACK,0.95f });
Application::UI::Panel* topbar_panel = new Application::UI::Panel({ 0,0 }, { 400, 30 }, { FLOAT_COLORS_GREEN });


auto* esp_inner = new Application::UI::Panel{ {0,-80},{400,420},{0,0,0,0} };
// ELEMENTS
auto* esp_checkbox = new Application::UI::Checkbox({ 20,-10 }, { 20,20 }, { FLOAT_COLORS_GRAY });
auto* name_checkbox = new Application::UI::Checkbox({ 20,-50 }, { 20,20 }, { FLOAT_COLORS_GRAY });


auto* aim_inner = new Application::UI::Panel{ {0,-80},{400,420},{0,0,0,0} };
// ELEMENTS
auto* aim_checkbox = new Application::UI::Checkbox({ 20,-10 }, { 20,20 }, { FLOAT_COLORS_GRAY });


auto* misc_inner = new Application::UI::Panel{ {0,-80},{400,420},{0,0,0,0} };
// ELEMENTS
auto* jump_checkbox = new Application::UI::Checkbox({ 20,-10 }, { 20,20 }, { FLOAT_COLORS_GRAY });
auto* car_sh_checkbox = new Application::UI::Checkbox({ 20,-50 }, { 20,20 }, { FLOAT_COLORS_GRAY });
auto* no_recoil_checkbox = new Application::UI::Checkbox({ 20,-90 }, { 20,20 }, { FLOAT_COLORS_GRAY });


#pragma endregion 

extern HMODULE DllInst;
extern DirectX::SpriteFont* VisbyRoundCFFont;

void MainMenuMarkup(Application::InteractiveForm* form)
{
	form->add_element(background_panel);
}
