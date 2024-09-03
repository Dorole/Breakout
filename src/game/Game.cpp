#include "Game.h"

using namespace sf;

Game::Game(RenderWindow& windowRef)
	: window(windowRef),
	valueGetter(levelLoader),
	audioPlayer(valueGetter),
	soundPlayer(valueGetter),
	collisionManager(windowRef),
	pool(valueGetter, soundPlayer),
	grid(valueGetter, pool, collisionManager)
{}