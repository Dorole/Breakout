#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collidable.h"
#include "CollidableObjectType.h"
//#include "CollidablesMap.h"

class CollisionManager
{
private:

	RenderWindow& window;
	std::unique_ptr<Collidable> ballCollidable;
	std::vector<std::unique_ptr<Collidable>> collidables;

	bool checkForCollision(std::unique_ptr<Collidable> collidable)
	{
		return ballCollidable->getSpriteGlobalBounds().intersects(collidable->getSpriteGlobalBounds());
	}

public:
	CollisionManager(RenderWindow& windowRef) : window(windowRef)
	{
		//CollidablesMap collMap(window); //test
	};

	void update()
	{
		
	}
	
	void registerBallCollidable(std::unique_ptr<Collidable> ballCollidable);
	void addCollidable(std::unique_ptr<Collidable> collidable);

};