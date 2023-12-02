#pragma once
#include "GameState.h"

#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "NumValueObserver.h"
#include "StateObserver.h"
#include "TextCreator.h"
#include "Button.h"


using namespace sf;

class MainMenuState : public GameState
{
private:

	std::vector<StateObserver*> stateObservers;

	Font font;
	std::unique_ptr<Text> titleText;
	int titleTextSize = 100;
	Button startButton;
	Button quitButton;

	std::string startText = "START";
	std::string quitText = "QUIT";
	Vector2f buttonSize { 200, 50 };
	int buttonTextSize = 50;
	Color buttonColor = Color::White;
	Color buttonTextColor = Color::Black;
	Vector2f buttonTextOffset { 0, 15};
	
	float buttonSpacing = 40;
	Vector2f startButtonPosition { window.getSize().x / 2.0f, (window.getSize().y / 2.0f) + 10 };
	Vector2f quitButtonPosition{ window.getSize().x / 2.0f, (window.getSize().y / 2.0f) + buttonSize.y + buttonSpacing};
	

public:

	MainMenuState(sf::RenderWindow& windowRef, ValueGetter& valueGetter);

	void init();
	virtual void handleInput() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;
	virtual void cleanup() override;
	virtual void attachValueObserver(NumValueObserver* observer) override;
	virtual void attachStateObserver(StateObserver* observer) override;

};