#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameState.h"
#include "utils/ValueGetter.h"
#include "audio/MusicPlayer.h"
#include "events/HUDObserver.h"
#include "events/StateObserver.h"
#include "events/InteractionObserver.h"
#include "UI/Button.h"

using namespace sf;

class MainMenuState : public GameState
{
private:

	bool isInit = false;
	std::vector<StateObserver*> stateObservers;

	std::unique_ptr<Text> titleText;
	float titleTextSizePercentage = 20.0f;
	float titleTextTopOffsetPercentage = 5.0f;
	
	Button startButton;
	Button soundButton;
	Button quitButton;
	std::vector<std::reference_wrapper<Button>> buttons
	{
		std::ref(startButton),
		std::ref(soundButton),
		std::ref(quitButton)
	};

	static const std::string GAME_TITLE;
	static const std::string MAIN_MENU_IMAGE_PATH;
	static const std::string START_TEXT;
	static const std::string QUIT_TEXT;
	static const std::string SOUND_ON;
	static const std::string SOUND_OFF;

	float buttonWidthPercentage = 25.0f;
	float buttonHeightPercentage = 10.0f;
	float buttonTextSizePercentage = 70.0f;
	float buttonSpacingPercentage = 5.0f;
	Vector2f buttonTextOffset{ 0, 30 };

	std::vector<InteractionObserver*> interactionObservers;
	bool isSoundOn = true;
	std::string toggleSound();

public:

	MainMenuState(Game& game);

	// Inherited via GameState
	virtual void init() override;
	virtual void onStateEnter() override;
	virtual void handleInput(Event& event) override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;
	virtual void onStateExit() override;
	virtual void setTextElements() override;
	virtual void setButtonElements() override;
	virtual void attachValueObserver(HUDObserver* observer) override;
	virtual void attachStateObserver(StateObserver* observer) override;
	
	void attachInteractionObserver(InteractionObserver* observer);
};

