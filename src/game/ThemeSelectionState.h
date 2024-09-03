#pragma once
#include "GameState.h"
#include "Game.h"
#include "UI/Button.h"
#include "UI/TextCreator.h"
#include "UI/LoadingScreen.h"
#include "events/ThemeSelectionObserver.h"

class ThemeSelectionState : public GameState
{
private:
	std::vector<StateObserver*> stateObservers;
	std::vector<ThemeSelectionObserver*> themeSelectionObservers;
	
	LoadingScreen loadingScreen;
	const std::string THEME_FONT = "ThemeFont";
	Font winterFont;
	Font summerFont;

	Button winterButton;
	Button summerButton;
	const std::string WINTER_TEXT = "WINTER";
	const std::string SUMMER_TEXT = "SUMMER";
	float buttonWidthPercentage = 25.0f;
	float buttonHeightPercentage = 10.0f;
	float buttonTextSizePercentage = 80;
	float buttonSpacingPercentage = 5.0f;
	Vector2f buttonTextOffset{ 0, 20 };

	const ThemeData& winterTheme = themeManager.getThemeData(Theme::WINTER);
	const ThemeData& summerTheme = themeManager.getThemeData(Theme::SUMMER);
	Color winterButtonColor = winterTheme.buttonColor;
	Color summerButtonColor = summerTheme.buttonColor;
	Color winterButtonTextColor = winterTheme.buttonTextColor;
	Color summerButtonTextColor = summerTheme.buttonTextColor;

	Theme selectedTheme = Theme::SUMMER;
	
	void attachThemeSelectionObserver(ThemeSelectionObserver* observer);
	void handleButtonInteraction(sf::Event& event, Button& button, Theme theme);
	void selfInit();
	void displayLoading();

public:
	ThemeSelectionState(Game& game);

	// Inherited via GameState
	virtual void init() override;
	virtual void onStateEnter() override;
	virtual void handleInput(sf::Event& event) override;
	virtual void update(float deltaTime) override;
	virtual void draw() override;
	virtual void onStateExit() override;
	virtual void setTextElements() override;
	virtual void setButtonElements() override;
	virtual void attachValueObserver(HUDObserver* observer) override;
	virtual void attachStateObserver(StateObserver* observer) override;
};

