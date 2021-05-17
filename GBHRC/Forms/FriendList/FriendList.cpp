#include "FriendList.h"

#include "FloatColors.h"
#include "../../resource.h"
#include "Render/Engine/Engine.h"
#include "Form/Interactive/elements/Panel/Panel.h"
#include "Form/Interactive/elements/Checkbox/Checkbox.h"
#include "Form/Interactive/elements/Label/Label.h"
#include "Form/Interactive/elements/Button/Button.h"
#include "../../CheatApi/GBHRC/gbhrc.h"

#define BUTTON_HEIGHT 30

auto* panel = new Application::UI::Panel({ -500,0 }, { 200,500 }, { FLOAT_COLORS_BLACK });
auto* frls_button_inner = new Application::UI::Panel({ 5,-BUTTON_HEIGHT -5 }, { 190,465 }, { FLOAT_COLORS_BLACK });
Application::UI::Panel* frls_topbar_panel = new Application::UI::Panel({ 0,0 }, { 200, 30 }, { FLOAT_COLORS_GREEN });

extern HMODULE DllInst;

void add_friend(Application::UI::InteractiveElement*element)
{
	auto* button = (Application::UI::Button*)element;
	auto* friend_name = (wchar_t*)button->text.get_text();
	auto* context = GBHRC::Context::instance();
	if (context->is_friend(friend_name))
	{
		context->remove_friend(friend_name);
		std::wcout << L"REMOVING: " << friend_name << '\n';
	}
	else
	{
		context->add_friend(friend_name);
		std::wcout << L"ADDING: " << friend_name << '\n';
	}
	button->non_active_color = { FLOAT_COLORS_GREEN };
}

void update_friend_list(int offset)
{
	auto* pcollection = BrokeProtocol::GetPlayersCollection()->items;

	auto iterator = pcollection->iterator();
	iterator.set_iteration(offset);
	int buttons_length = frls_button_inner->get_resolution().height / (BUTTON_HEIGHT+5);

	auto* local_player = BrokeProtocol::GetLocalPlayer();

	for(int i =offset;i<buttons_length;i++)
	{
		auto* button = (Application::UI::Button*)frls_button_inner->element_at(i);

		if (iterator.next())
		{
			if (iterator.item() == local_player)
				if (!iterator.next())
				{
					button->hidden = true;
					return;
				}
			
			button->text.set_text((const wchar_t*)&iterator.item()->username->array);
			button->onClick = add_friend;
			button->hidden = false;

			if(GBHRC::Context::instance()->is_friend((wchar_t*)button->text.get_text()))
			{
				button->non_active_color = { FLOAT_COLORS_GREEN };
			}else
			{
				button->non_active_color = { FLOAT_COLORS_GRAY };
			}
		}else
		{
			button->hidden = true;
		}
	}
}

void FiendListMarkup(Application::InteractiveForm* form, Application::Render::Engine* pEngine)
{
	auto* esp_font = pEngine->create_font(
		(void*)LoadResource(DllInst, FindResourceW(DllInst, MAKEINTRESOURCE(IDR_VISBY_ROUND), L"SPRITEFONT")),
		0x6608
	);
	
	form->add_element(panel);

	panel
		->add_element(
			frls_topbar_panel
			->add_element(new Application::UI::Label{ {0,0},"FRIENDS",esp_font,{FLOAT_COLORS_WHITE},{200,30} })
		)
		->add_element(frls_button_inner)
	;

	for(float i =0;i<13;i++)
	{
		frls_button_inner->add_element(new Application::UI::Button({ 0,(i * (BUTTON_HEIGHT + 5) )*-1 }, { 190,30 }, { FLOAT_COLORS_GRAY }, esp_font, "alyykes228"));
	}

	form->initialize_components(pEngine);

	
	frls_button_inner->onMouseScroll = [](Application::UI::UIElementEventArgs args,int delta)
	{
		static int offset=0;
		auto off = (delta / 120)*-1;
		if(offset + off < 0)
			offset = 0;
		else {
			auto size = BrokeProtocol::GetPlayersCollection()->items->size();
			if (offset + off <= size)
				offset += off;
			else
				offset = size;
		}
		
		update_friend_list(offset);
	};


	{
		auto resolut = panel->get_resolution();
		panel->move_by(0, resolut.height / 2);
	}
}
