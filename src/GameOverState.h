#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "GameState.h"
#include "ValueGetter.h"
#include "MusicPlayer.h"
#include "LevelLoader.h"
#include "Button.h"
#include "StateObserver.h"
#include "NumValueObserver.h"
#include "LevelDataObserver.h"

using namespace sf;

class GameOverState : public GameState, public NumValueObserver, public LevelDataObserver
{
private:

	LevelLoader& levelLoader;
	LoadLevelMode currentMode;
	State nextState;
	std::vector<StateObserver*> stateObservers;;

	int totalScore { 0 };

	Font font;
	std::unique_ptr<Text> gameOverText;
	std::unique_ptr<Text> totalScoreText;
	Color textColor = Color(0, 0, 102);
	float gameOverTextPercentage = 20.0f;
	float scoreTextPercentage = 10.0f;
	float gameOverTextTopOffsetPercentage = 3.0f;
	float verticalTextSpacingPercentage = 5.0f;

	const std::string GAME_OVER_LABEL = "GAME OVER";
	const std::string SCORE_LABEL = "TOTAL SCORE: ";

	Button restartButton;
	Button menuButton;

	const std::string RESTART_TEXT = "RESTART";
	const std::string MENU_TEXT = "MENU";
	float buttonWidthPercentage = 25.0f;
	float buttonHeightPercentage = 10.0f;
	float buttonTextSizePercentage = 80.0f;
	float buttonSpacingPercentage = 5.0f;
	Color buttonColor = Color::White;
	Color buttonTextColor = textColor;
	Vector2f buttonTextOffset{ 0, 30 };


public:

	GameOverState(Game& game);

	void init();

	// Inherited via GameState
	virtual void onStateEnter() override;
	virtual void handleInput() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;
	virtual void onStateExit() override;
	virtual void setTextElements() override;
	virtual void setButtonElements() override;
	virtual void attachValueObserver(NumValueObserver* observer) override;
	virtual void attachStateObserver(StateObserver* observer) override;

	// Inherited via NumValueObserver
	virtual void onValueChanged(int value, ValueType valueType) override;

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;

};

