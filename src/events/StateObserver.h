#pragma once

enum class State
{
	THEME_SELECT,
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

