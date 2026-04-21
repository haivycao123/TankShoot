#define NOMINMAX // Ngăn chặn định nghĩa macro min và max
#define WIN32_LEAN_AND_MEAN // Giảm kích thước của các header Windows
#include "GameStateBase.h"
#include "../GameState/GSIntro.h"
#include "../GameState/GSMenu.h"
#include "../GameState/GSPlay.h"
#include "../GameState/GSEnd.h"
#include "../GameState/GSSetting.h"
#include "../GameState/GSAbout.h"
#include "../GameState/GSPause.h"

GameStateBase* GameStateBase::CreateState(StateTypes st) {
	GameStateBase* gs = nullptr;
	switch (st)
	{
	case INVALID:
		break;
	case INTRO:
		gs = new GSIntro();
		break;
	case MENU:
		gs = new GSMenu();
		break;
	case PLAY:
		gs = new GSPlay();
		break;
	case SETTING:
		gs = new GSSetting();
		break;
	case ABOUT:
		gs = new GSAbout();
		break;
	case PAUSE: 
		gs = new GSPause();
		break;
	case END:
		gs = new GSEnd();
		break;
	default:
		break;
	}
	return gs;
}