#pragma once
#include <vector>
#include <iostream>
#include "Collidable.h"
#include "CollidableObjectType.h"

class CollisionManager
{
private:

	std::unique_ptr<Collidable> ballCollidable;
	std::vector<std::unique_ptr<Collidable>> collidables;

public:
	CollisionManager() {};

	void update()
	{
		
	}
	
	void registerBallCollidable(std::unique_ptr<Collidable> ballCollidable);
	void addCollidable(std::unique_ptr<Collidable> collidable);

};