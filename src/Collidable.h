#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SpritePosition.h"
#include "CollidableObjectType.h"


using namespace sf;

class Collidable
{
private:
	CollidableObjectType objectType = CollidableObjectType::BRICK;
	SpritePosition spritePosition = SpritePosition::TOP_LEFT;

	Sprite& sprite;
	Vector2f position;

public:
	Collidable(Sprite& spriteRef, CollidableObjectType objectTypeInit);

	void setCollidableObjectType(CollidableObjectType type);
	CollidableObjectType getCollidableObjectType() { return objectType; }

	const Sprite& getSprite() const { return sprite; }

	void setSpritePosition(SpritePosition pos);
	SpritePosition getSpritePosition() { return spritePosition; }

	Vector2f getGlobalSpritePosition() { return sprite.getPosition(); }
	FloatRect getSpriteGlobalBounds() { return sprite.getGlobalBounds(); }

	//void checkSprite(Sprite& _sprite)
	//{
	//	if (sprite.getTexture() == _sprite.getTexture())
	//		std::cout << "Textures match" << std::endl;
	//	else
	//		std::cout << "No textures match" << std::endl;
	//}
};

