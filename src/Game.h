#pragma once
#include <SFML/Graphics.hpp>
#include "XmlParser.h"
#include "GameObject.h"
#include "Platform.h"
#include "ValueGetter.h"

using namespace sf;

class Game
{
private:
	RenderWindow& window;
	ValueGetter& valueGetter;
	std::vector<std::unique_ptr<GameObject>> gameObjects;
	XmlParser parser;

public:
	Game(RenderWindow& windowRef, ValueGetter& valueGetterRef);

	void update();
	void render();
};

