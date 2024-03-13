#pragma once
#include <SFML/Graphics.hpp>
#include "CollidablesMap.h"
#include "Collidable.h"

class CollisionManager
{
private:
	RenderWindow& window;
	CollidablesMap colMap;

public:
	CollisionManager(RenderWindow& windowRef)
		: window(windowRef)
	{};

	//void addCollidableToCollisionMap(std::unique_ptr<Collidable> collidable)
	//{
	//	colMap.addCollidableToVector(std::move(collidable));
	//}
};