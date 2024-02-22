#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayerController //mozda nije dobro ime
{
public:

	virtual Vector2f getInitialPosition() const = 0;
	virtual Vector2f getPosition() const = 0;
	virtual bool getWindowBoundReached() const = 0;
	virtual FloatRect getLocalBounds() const = 0;
	virtual FloatRect getGlobalBounds() const = 0;
};

