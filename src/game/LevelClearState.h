#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Game.h"
#include "utils/ValueGetter.h"
#include "audio/MusicPlayer.h"
#include "LevelLoader.h"
#include "UI/Button.h"
#include "events/StateObserver.h"
#include "events/HUDObserver.h"
#include "events/LevelDataObserver.h"

using namespace sf;

class LevelClearState : public GameState, public HUDObserver, public LevelDataObserver
{
private:
	LevelLoader& levelLoader;

	LoadLevelMode currentMode = LoadLevelMode::PROGRESS;
	State nextState = State::PLAYING_STATE;
	std::vector<StateObserver*> stateObservers;

	int totalScore{ 0 };

	std::unique_ptr<Text> levelClearText;
	std::unique_ptr<Text> totalScoreText;

	float levelClearTextPercentage = 20.0f;
	float scoreTextPercentage = 10.0f;
	float levelClearTopOffsetPercentage = 3.0f;
	float verticalTextSpacingPercentage = 5.0f;

	static const std::string LEVEL_CLEAR_IMAGE;
	static const std::string LEVEL_CLEAR_LABEL;
	static const std::string GAME_CLEAR_LABEL;
	static const std::string SCORE_LABEL;
	static const std::string RESTART_TEXT;
	static const std::string NEXT_TEXT;
	static const std::string MENU_TEXT;

	Button nextButton;
	Button restartButton;
	Button menuButton;
	std::vector<std::reference_wrapper<Button>> buttons
	{
		std::ref(nextButton),
		std::ref(restartButton),
		std::ref(menuButton)
	};

	float buttonWidthPercentage = 25.0f;
	float buttonHeightPercentage = 10.0f;
	float buttonTextSizePercentage = 80.0f;
	float buttonSpacingPercentage = 5.0f;
	Vector2f buttonTextOffset{ 0, 30 };

public:

	LevelClearState(Game& game);

	void init();

	// Inherited via GameState
	virtual void onStateEnter() override;
	virtual void handleInput(Event& event) override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;
	virtual void onStateExit() override;
	virtual void setTextElements() override;
	virtual void setButtonElements() override;
	virtual void attachValueObserver(HUDObserver* observer) override;
	virtual void attachStateObserver(StateObserver* observer) override;

	// Inherited via NumValueObserver
	virtual void onValueChanged(int value, ValueType valueType) override;

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;

};

