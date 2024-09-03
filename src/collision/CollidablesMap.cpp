#include "CollidablesMap.h"

CollidablesMap::CollidablesMap(RenderWindow& window)
{
	calculateMidPoints(window);
}

void CollidablesMap::calculateMidPoints(RenderWindow& window)
{
	midX = window.getSize().x / 2.0f;
	midY = window.getSize().y / 2.0f;
}

void CollidablesMap::mapCollidable(Collidable& collidable, SpritePosition pos)
{
	auto& vec = collidablesMap[pos];
	vec.push_back(collidable);
}

std::vector<SpritePosition> CollidablesMap::getRelevantAreas(SpritePosition mainQuadrant)
{
	switch (mainQuadrant)
	{
	case SpritePosition::TOP_LEFT:
		return {
			SpritePosition::TOP_LEFT,
			SpritePosition::TOP_CENTRE,
			SpritePosition::LEFT_CENTRE,
			SpritePosition::CENTRE
		};

	case SpritePosition::TOP_RIGHT:
		return {
			SpritePosition::TOP_RIGHT,
			SpritePosition::TOP_CENTRE,
			SpritePosition::RIGHT_CENTRE,
			SpritePosition::CENTRE
		};

	case SpritePosition::BOTTOM_LEFT:
		return {
			SpritePosition::BOTTOM_LEFT,
			SpritePosition::BOTTOM_CENTRE,
			SpritePosition::LEFT_CENTRE,
			SpritePosition::CENTRE
		};

	case SpritePosition::BOTTOM_RIGHT:
		return {
			SpritePosition::BOTTOM_RIGHT,
			SpritePosition::BOTTOM_CENTRE,
			SpritePosition::RIGHT_CENTRE,
			SpritePosition::CENTRE
		};

	default:
		return {};
	}
}

void CollidablesMap::setCollidablePosition(Collidable& collidable)
{
	FloatRect spriteBounds = collidable.getSpriteGlobalBounds();
	SpritePosition position{ SpritePosition::TOP_LEFT };

	if (spriteBounds.top < midY && (spriteBounds.top + spriteBounds.height) < midY)
	{
		if (spriteBounds.left < midX && (spriteBounds.left + spriteBounds.width) < midX)
			position = SpritePosition::TOP_LEFT;
		else if (spriteBounds.left > midX && (spriteBounds.left + spriteBounds.width) > midX)
			position = SpritePosition::TOP_RIGHT;
		else
			position = SpritePosition::TOP_CENTRE;
	}
	else if (spriteBounds.top > midY && (spriteBounds.top + spriteBounds.height) > midY)
	{
		if (spriteBounds.left < midX && (spriteBounds.left + spriteBounds.width) < midX)
			position = SpritePosition::BOTTOM_LEFT;
		else if (spriteBounds.left > midX && (spriteBounds.left + spriteBounds.width) > midX)
			position = SpritePosition::BOTTOM_RIGHT;
		else
			position = SpritePosition::BOTTOM_CENTRE;
	}
	else if (spriteBounds.top < midY && (spriteBounds.top + spriteBounds.height) > midY)
	{
		if (spriteBounds.left < midX && (spriteBounds.left + spriteBounds.width) < midX)
			position = SpritePosition::LEFT_CENTRE;
		else if (spriteBounds.left > midX && (spriteBounds.left + spriteBounds.width) > midX)
			position = SpritePosition::RIGHT_CENTRE;
		else
			position = SpritePosition::CENTRE;
	}

	collidable.setSpritePosition(position);
}

void CollidablesMap::mapCollidablePosition(Collidable& collidable)
{
	if (collidable.getCollidableObjectType() == CollidableObjectType::PLATFORM)
	{
		SpritePosition platformPos = SpritePosition::BOTTOM_CENTRE;
		collidable.setSpritePosition(platformPos);
	}
	else
	{
		setCollidablePosition(collidable);
	}

	mapCollidable(collidable, collidable.getSpritePosition());

}

SpritePosition CollidablesMap::getCurrentPosition(Collidable& collidable)
{
	Vector2f globalSpritePosition = collidable.getGlobalSpritePosition();
	SpritePosition position{ SpritePosition::TOP_LEFT };

	if (globalSpritePosition.x < midX)
	{
		if (globalSpritePosition.y < midY)
			position = SpritePosition::TOP_LEFT;
		else if (globalSpritePosition.y > midY)
			position = SpritePosition::BOTTOM_LEFT;
	}
	else if (globalSpritePosition.x > midX)
	{
		if (globalSpritePosition.y < midY)
			position = SpritePosition::TOP_RIGHT;
		else if (globalSpritePosition.y > midY)
			position = SpritePosition::BOTTOM_RIGHT;
	}

	return position;
}

void CollidablesMap::clearCollidablesMap()
{
	for (auto& entry : collidablesMap) {
		entry.second.clear();
	}
}