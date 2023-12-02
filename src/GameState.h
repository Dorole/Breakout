#pragma once
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "NumValueObserver.h"

class GameState
{
private:
	void baseInit();

protected:
	sf::RenderWindow& window;
	ValueGetter& valueGetter;

public:

	GameState(sf::RenderWindow& windowRef, ValueGetter& valueGetterRef);
	
	virtual void handleInput() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;
	virtual void cleanup() = 0;

	virtual void attachObserver(NumValueObserver* observer) = 0;

	virtual ~GameState() = default;

};
