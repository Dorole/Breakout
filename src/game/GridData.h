#pragma once
#include <SFML/Graphics.hpp>
#include "objects/Brick.h"
#include "collision/Collidable.h"
#include "collision/CollisionManager.h"

struct GridData
{
	std::shared_ptr<Brick> brickData {};
	bool shouldRender{ false };
	bool canDestroy{ false };

	Sprite& getBrickSprite()
	{
		return brickData->getSprite();
	}

	FloatRect& getBrickSpriteBounds()
	{
		return brickData->getSpriteBounds();
	}

	void setSpritePosition(Vector2f position)
	{
		brickData->setSpritePosition(position);
	}

	FloatRect getSpriteGlobalBounds()
	{
		return brickData->getSpriteGlobalBounds();
	}

	bool shouldDestroy()
	{
		return brickData->shouldDestroy();
	}

	std::string getBrickId()
	{
		return brickData->getBrickId();
	}

	Collidable& getCollidable()
	{
		return brickData->getCollidable();
	}

	void attachCollisionObserver(CollisionManager& collisionManager)
	{
		brickData->observeCollision(collisionManager);
	}

	~GridData() {};
};