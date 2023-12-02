#pragma once
#include "GameState.h"

enum class State
{
	MAIN_MENU,
	PLAYING_STATE,
	GAME_OVER,
	LEVEL_CLEAR
};

class StateObserver
{
public:
	virtual void onStateChanged(State state) = 0;
};
