#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ValueGetter.h"
#include "BrickGrid.h"
#include "Platform.h"

using namespace sf;

class Game
{
private:
	RenderWindow& window;
	ValueGetter& valueGetter;
	BrickGrid& grid;

	std::vector<std::unique_ptr<GameObject>> gameObjects;

public:
	Game(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& grid);

	void update();
	void render();
};

