#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "utils/ValueGetter.h"
#include "TextCreator.h"
#include "Button.h"
#include "game/Game.h"
#include "events/HUDObserver.h"
#include "events/LevelDataObserver.h"
#include "events/InteractionObserver.h"
#include "ThemeManager.h"
#include "ImageConfig.h"

using namespace sf;

class UIManager : public HUDObserver, public LevelDataObserver
{
private:
	RenderWindow& window;
	ValueGetter& valueGetter;
	const ThemeData* currentTheme = nullptr;

	static const std::string PAUSE_SCREEN;
	static const std::string FONT_PATH;
	static const std::string PAUSED_TEXT;
	static const std::string RESUME_TEXT;
	static const std::string MENU_TEXT;

	TextCreator textCreator;
	Font font;
	float verticalSpacing = 25;
	float fontSizePercentage = 7.0f;
	float textOffsetTopPercentage = 1.0f;
	float textOffsetSidePercentage = 10.0f;
	std::unique_ptr<Text> levelValueText;
	std::unique_ptr<Text> scoreValueText;
	std::unique_ptr<Text> currentLivesText;
	std::vector<std::unique_ptr<Text>> labelTexts;
	Vector2f adjustedScorePosition{};

	bool paused = false;
	
	ImageConfig imageConfig;
	Texture bgTexture;
	Sprite pauseBackground;
	std::unique_ptr<Text> pausedText;
	Button resumeButton;
	Button menuButton;
	std::vector<std::reference_wrapper<Button>> buttons
	{
		std::ref(resumeButton),
		std::ref(menuButton)
	};

	float pauseTextSizePercentage = 15.0f;
	float pauseTextTopOffsetPercentage = 5.0f;
	float buttonWidthPercentage = 25.0f;
	float buttonHeightPercentage = 10.0f;
	float buttonTextSizePercentage = 80;
	float buttonSpacingPercentage = 5.0f;
	Vector2f buttonTextOffset{ 0, 30 };

	std::vector<InteractionObserver*> interactionObservers;

	void setTextElements();
	void setHUDTextElements();
	void setPauseTextElements();
	void setButtonElements();
	void setBackgroundImage();

public:

	UIManager(RenderWindow& windowRef, Game& game);

	void handleInput(sf::Event& event);
	void update();
	void draw();
	void togglePause();
	void attachInteractionObserver(InteractionObserver* observer);

	// Inherited via HUDObserver
	void onValueChanged(int value, ValueType valueType) override;

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;
};




