#pragma once
#include <SFML/Graphics.hpp>
#include "game/Game.h"
#include "utils/ValueGetter.h"
#include "collision/CollisionManager.h"

using namespace sf;

class GameObject
{
protected:
	RenderWindow& window;
	ValueGetter& valueGetter;
	CollisionManager& collisionManager;
	LevelDataProvider& levelDataProvider;

public:
	GameObject(Game& game);

	virtual void preconfigure() {};
	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;

	virtual void registerForCollision() { return; }
};



