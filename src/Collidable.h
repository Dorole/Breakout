#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SpritePosition.h"
#include "CollidableObjectType.h"


class Collidable
{
private:
	CollidableObjectType objectType = CollidableObjectType::BRICK;
	SpritePosition spritePosition = SpritePosition::TOP_LEFT;

	const sf::Sprite& sprite;

	bool isActive = true;

public:
	Collidable(const sf::Sprite& spriteRef, CollidableObjectType objectTypeInit);

	void setCollidableObjectType(CollidableObjectType type);
	CollidableObjectType getCollidableObjectType() { return objectType; }

	const sf::Sprite& getSprite() const { return sprite; }

	void setSpritePosition(SpritePosition pos);
	SpritePosition getSpritePosition() { return spritePosition; }

	sf::Vector2f getGlobalSpritePosition() { return sprite.getPosition(); }
	sf::FloatRect getSpriteGlobalBounds() { return sprite.getGlobalBounds(); }
	sf::FloatRect getSpriteLocalBounds() { return sprite.getLocalBounds(); }

	bool getActiveStatus() const { return isActive; }
	void setActiveStatus(bool value) { isActive = value; }

};

