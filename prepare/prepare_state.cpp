#include "prepare_state.h"
#include <thread>
#include "../gui/button.h"
#include "../sprite.h"
#include "../system.h"
#include "../control_handler.h"
#include "../texture_manager.h"
#include "../loading/loading_state.h"
#include "../user/user_profile.h"
#include "../background.h"
#include "song_list.h"
#include "prepare_header.h"
#include "mod_widget.h"
#include "list_widget.h"

fr::PrepareState *fr::PrepareState::m_instance = 0;

void fr::PrepareState::init()
{
	PrepareHeader::instance()->init();
	SongList::instance()->init();
	ModWidget::instance()->init();
	ListWidget::instance()->init();
	prepare_back = new Button;
	prepare_mod = new Button;
	prepare_list = new Button;
	prepare_refresh = new Button;
	background = new Sprite;

	prepare_back->init("assets/base/sort_button.png");
	prepare_back->AddPressedFrame( "assets/base/sort_button_pressed.png");
	prepare_mod->init("assets/base/sort_button.png", Rect(0, 72, 0, 0));
	prepare_mod->AddPressedFrame( "assets/base/sort_button_pressed.png");
	prepare_list->init("assets/base/sort_button.png", Rect(0, 144, 0, 0));
	prepare_list->AddPressedFrame( "assets/base/sort_button_pressed.png");
	prepare_refresh->init("assets/base/sort_button.png", Rect(0, 216, 0, 0));
	prepare_refresh->AddPressedFrame( "assets/base/sort_button_pressed.png");

	prepare_back->AddText("Back", prepare_back->GetW() / 2, prepare_back->GetH() / 2, "assets/fonts/Audiowide.ttf", 36, 0x00, 0x00, 0x00);
	prepare_mod->AddText("Mod", prepare_mod->GetW() / 2, prepare_mod->GetH() / 2, "assets/fonts/Audiowide.ttf", 36, 0x00, 0x00, 0x00);
	prepare_list->AddText("List", prepare_list->GetW() / 2, prepare_list->GetH() / 2, "assets/fonts/Audiowide.ttf", 36, 0x00, 0x00, 0x00);
	prepare_refresh->AddText("Refresh", prepare_refresh->GetW() / 2, prepare_refresh->GetH() / 2, "assets/fonts/Audiowide.ttf", 32, 0x00, 0x00, 0x00);

	if (System::instance()->GetWindowRotation() == WINDOWROTATION_PORTRAIT)
	{
		prepare_back->SetPos(0, 0);
		prepare_mod->SetPos(0, 72);
		prepare_list->SetPos(0, 144);
		prepare_refresh->SetPos(0, 216);
	}
	else
	{
		prepare_back->SetPos(0, System::instance()->GetWindowHeigh() - 72);
		prepare_mod->SetPos(System::instance()->GetWindowWidth() - 160, System::instance()->GetWindowHeigh() - 72);
		prepare_list->SetPos(System::instance()->GetWindowWidth() - 160, System::instance()->GetWindowHeigh() - 144);
		prepare_refresh->SetPos(0, System::instance()->GetWindowHeigh() - 144);
	}
}	//void fr::PrepareState::init()

void fr::PrepareState::clear()
{
	SongList::instance()->clear();
	background->clear();
}

void fr::PrepareState::update()
{
	if (System::instance()->IsWindowModified())
	{
		if (System::instance()->GetWindowRotation() == WINDOWROTATION_PORTRAIT)
		{
			prepare_back->SetPos(0, 0);
			prepare_mod->SetPos(0, 72);
			prepare_list->SetPos(0, 144);
			prepare_refresh->SetPos(0, 216);
		}
		else
		{
			prepare_back->SetPos(0, System::instance()->GetWindowHeigh() - 72);
			prepare_mod->SetPos(System::instance()->GetWindowWidth() - 160, System::instance()->GetWindowHeigh() - 72);
			prepare_list->SetPos(System::instance()->GetWindowWidth() - 160, System::instance()->GetWindowHeigh() - 144);
			prepare_refresh->SetPos(0, System::instance()->GetWindowHeigh() - 144);
		}
	}

	SongList::instance()->update();
	PrepareHeader::instance()->update();
	ModWidget::instance()->update();
	ListWidget::instance()->update();
	prepare_back->update();
	prepare_mod->update();
	prepare_list->update();
	prepare_refresh->update();

	Background::instance()->render();
	SongList::instance()->render();
	PrepareHeader::instance()->render();
	prepare_back->render();
	prepare_mod->render();
	prepare_list->render();
	prepare_refresh->render();
	ModWidget::instance()->render();
	ListWidget::instance()->render();
	if (!ModWidget::instance()->IsShown() && !ListWidget::instance()->IsShown())
	{
		if (prepare_back->IsReleased() || ControlHandler::instance()->IsKeyDown(SDL_SCANCODE_AC_BACK))
		{
			LoadingState::instance()->init(STATE_MAIN);
		}
		if (prepare_mod->IsReleased())
		{
			ModWidget::instance()->SwitchShown();
		}
		if (prepare_list->IsReleased())
		{
			ListWidget::instance()->SwitchShown();
		}
		if (prepare_refresh->IsReleased() && !SongList::instance()->IsRefreshing())
		{
			std::thread refresh_thread(&fr::SongList::RefreshList);
			refresh_thread.detach();
		}
	}
}	//void fr::PrepareState::update()