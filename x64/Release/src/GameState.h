#pragma once
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "MusicPlayer.h"
#include "NumValueObserver.h"
#include "StateObserver.h"
#include "ImageConfig.h"

class GameState
{
private:
	void baseInit();

protected:
	sf::RenderWindow& window;
	ValueGetter& valueGetter;
	MusicPlayer& audioPlayer;

	Texture bgTexture;
	Sprite bgImage;
	ImageConfig imageConfig;

	void setBackground(std::string texturePath);

public:
	GameState(sf::RenderWindow& windowRef, ValueGetter& valueGetterRef, MusicPlayer& audioPlayerRef);
	
	virtual void onStateEnter() = 0;
	virtual void handleInput() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
	virtual void onStateExit() = 0;

	virtual void setTextElements() = 0;
	virtual void setButtonElements() = 0;

	virtual void attachValueObserver(NumValueObserver* observer) = 0;
	virtual void attachStateObserver(StateObserver* observer) = 0;

	virtual ~GameState() = default;

};
