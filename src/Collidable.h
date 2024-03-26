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

	sf::Sprite& sprite;
	sf::Vector2f position;

public:
	Collidable(sf::Sprite& spriteRef, CollidableObjectType objectTypeInit);

	void setCollidableObjectType(CollidableObjectType type);
	CollidableObjectType getCollidableObjectType() { return objectType; }

	const sf::Sprite& getSprite() const { return sprite; }

	void setSpritePosition(SpritePosition pos);
	SpritePosition getSpritePosition() { return spritePosition; }

	sf::Vector2f getGlobalSpritePosition() { return sprite.getPosition(); }
	sf::FloatRect getSpriteGlobalBounds() { return sprite.getGlobalBounds(); }
	sf::FloatRect getSpriteLocalBounds() { return sprite.getLocalBounds(); }
	
};

