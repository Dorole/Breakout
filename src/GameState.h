#pragma once
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "AudioPlayer.h"
#include "NumValueObserver.h"
#include "StateObserver.h"

class GameState
{
private:
	void baseInit();

protected:
	sf::RenderWindow& window;
	ValueGetter& valueGetter;
	AudioPlayer& audioPlayer;

public:
	GameState(sf::RenderWindow& windowRef, ValueGetter& valueGetterRef, AudioPlayer& audioPlayerRef);
	
	virtual void onStateEnter() = 0;
	virtual void handleInput() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
	virtual void onStateExit() = 0;

	virtual void attachValueObserver(NumValueObserver* observer) = 0;
	virtual void attachStateObserver(StateObserver* observer) = 0;

	virtual ~GameState() = default;

};
