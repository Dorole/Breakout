#pragma once
#include <SFML/Graphics.hpp>
#include "Brick.h"


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

	~GridData() {};
};