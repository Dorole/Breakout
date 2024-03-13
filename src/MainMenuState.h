#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameState.h"
#include "ValueGetter.h"
#include "MusicPlayer.h"
#include "NumValueObserver.h"
#include "StateObserver.h"
#include "Button.h"

using namespace sf;

class MainMenuState : public GameState
{
private:

	std::vector<StateObserver*> stateObservers;

	Font font;
	std::unique_ptr<Text> titleText;
	float titleTextSizePercentage = 20.0f;
	float titleTextTopOffsetPercentage = 5.0f;
	Color titleTextColor = Color(0, 0, 102); //deep blue
	Button startButton;
	Button quitButton;

	std::string startText = "START";
	std::string quitText = "QUIT";
	float buttonWidthPercentage = 25.0f;
	float buttonHeightPercentage = 10.0f;
	float buttonTextSizePercentage = 80;
	float buttonSpacingPercentage = 5.0f;
	Color buttonColor = Color::White;
	Color buttonTextColor = titleTextColor;
	Vector2f buttonTextOffset{ 0, 30 };

	SoundPlayer soundPlayer;

public:

	MainMenuState(Game& game);

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

};