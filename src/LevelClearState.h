#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "ValueGetter.h"
#include "GameConfig.h"
#include "Button.h"
#include "StateObserver.h"
#include "NumValueObserver.h"
#include "LevelDataObserver.h"

using namespace sf;

class LevelClearState : public GameState, public NumValueObserver, public LevelDataObserver
{
private:
	GameConfig& gameConfig;

	LoadLevelMode currentMode;
	State nextState;
	std::vector<StateObserver*> stateObservers;;

	int totalScore{ 0 };

	Font font;
	std::unique_ptr<Text> levelClearText;
	std::unique_ptr<Text> totalScoreText;

	int levelClearTextSize = 100;
	int scoreTextSize = 50;
	int verticalTextSpacing = 50;
	const std::string LEVEL_CLEAR_LABEL = "LEVEL CLEAR!";
	const std::string SCORE_LABEL = "TOTAL SCORE: ";

	Button nextButton;
	Button restartButton;
	Button menuButton;

	const std::string RESTART_TEXT = "RESTART";
	const std::string NEXT_TEXT = "NEXT";
	const std::string MENU_TEXT = "MENU";
	Vector2f buttonSize{ 250, 60 };
	int buttonTextSize = 50;
	Color buttonColor = Color::White;
	Color buttonTextColor = Color::Black;
	Vector2f buttonTextOffset{ 0, 15 };

	float buttonSpacing = 30;
	Vector2f nextButtonPosition{ window.getSize().x / 2.0f, (window.getSize().y / 2.0f) + buttonSpacing };
	Vector2f restartButtonPosition{ window.getSize().x / 2.0f, (window.getSize().y / 2.0f) + buttonSize.y + (buttonSpacing * 1.5f) };
	Vector2f menuButtonPosition{ window.getSize().x / 2.0f, (window.getSize().y / 2.0f) + (buttonSize.y * 2) + (buttonSpacing * 2) };

public:

	LevelClearState(RenderWindow& windowRef, ValueGetter& valueGetterRef, GameConfig& gameConfigRef);

	void init();

	// Inherited via GameState
	virtual void onStateEnter() override;
	virtual void handleInput() override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;
	virtual void onStateExit() override;
	virtual void attachValueObserver(NumValueObserver* observer) override;
	virtual void attachStateObserver(StateObserver* observer) override;

	// Inherited via NumValueObserver
	virtual void onValueChanged(int value, ValueType valueType) override;

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;
};
