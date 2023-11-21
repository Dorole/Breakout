#pragma once
#include <SFML/Graphics.hpp>
#include "XmlParser.h"
#include "GameObject.h"
#include "Platform.h"

using namespace sf;

class Game
{
private:
	RenderWindow& window;
	std::vector<std::unique_ptr<GameObject>> gameObjects;
	XmlParser parser;

public:
	Game(RenderWindow& windowRef);

	void update();
	void render();
};

