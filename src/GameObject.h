#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ValueGetter.h"
#include "LevelDataObserver.h"
#include "CollisionManager.h"

using namespace sf;

class GameObject : public LevelDataObserver
{
protected:
	RenderWindow& window;
	ValueGetter& valueGetter;
	CollisionManager& collisionManager;
	LevelDataProvider& levelDataProvider;

public:
	GameObject(Game& game);

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;

	virtual void registerForCollision() { return; }

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;
};

