#pragma once
#include <SFML/Graphics.hpp>

class GameObjectData
{
private:
	const sf::Sprite& sprite;
	sf::Vector2f spriteInitialPosition;

public:
	GameObjectData(const sf::Sprite& spriteRef) : sprite(spriteRef) {}

	const sf::Sprite& getSprite() const { return sprite; }

	sf::Vector2f getGlobalSpritePosition() { return sprite.getPosition(); }
	sf::FloatRect getSpriteGlobalBounds() { return sprite.getGlobalBounds(); }
	sf::FloatRect getSpriteLocalBounds() { return sprite.getLocalBounds(); }

	void setSpriteInitialPosition(sf::Vector2f pos)
	{
		spriteInitialPosition = pos;
	}

	sf::Vector2f getSpriteInitialPosition() const { return spriteInitialPosition; }
};

