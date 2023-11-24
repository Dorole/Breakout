#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;

};

