#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "utils/ValueGetter.h"
#include "audio/MusicPlayer.h"
#include "events/HUDObserver.h"
#include "events/StateObserver.h"
#include "events/InitReadyObserver.h"
#include "ui/ImageConfig.h"
#include "ui/ThemeManager.h"
#include "ui/LoadingScreen.h"

using namespace sf;

class GameState : public InitReadyObserver
{
protected:
	sf::RenderWindow& window;
	ValueGetter& valueGetter;
	MusicPlayer& audioPlayer;
	ThemeManager& themeManager;
	LoadingScreen loadingScreen;

	static const std::string FONT_PATH;
	Font font;
	Texture bgTexture;
	Sprite bgImage;
	ImageConfig imageConfig;
	sf::Color buttonColor;
	sf::Color buttonTextColor;
	sf::Color textColor;
	sf::Color hudColor;
	sf::Color titleColor;
	sf::Color outlineColor;
	float outlineThickness{0};

	void setBackground(std::string texturePath);
	void updateThematicElements();
	void displayLoading();

public:
	GameState(Game& gameRef);

	virtual void init() = 0;
	virtual void onStateEnter() = 0;
	virtual void handleInput(sf::Event& event) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
	virtual void onStateExit() = 0;

	virtual void setTextElements() = 0;
	virtual void setButtonElements() = 0;

	virtual void attachValueObserver(HUDObserver* observer) = 0;
	virtual void attachStateObserver(StateObserver* observer) = 0;


	// Inherited via InitReadyObserver
	virtual void onInit() override;

	virtual ~GameState() = default;

};


