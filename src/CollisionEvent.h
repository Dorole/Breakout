#pragma once
#include <SFML/Graphics.hpp>

struct CollisionEvent
{
	sf::FloatRect collidableLocalBounds;
	sf::FloatRect collidableGlobalBounds;
	sf::Vector2f collidablePosition;
};

