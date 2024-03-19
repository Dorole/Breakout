#include "CollisionManager.h"

void CollisionManager::registerBallCollidable(std::unique_ptr<Collidable> ballCollidable)
{
	if (ballCollidable->getCollidableObjectType() != CollidableObjectType::BALL)
	{
		std::cerr << "ERROR: Tried to register something other than Ball Collidable as Ball Collidable!" << std::endl;
		return;
	}

	this->ballCollidable = std::move(ballCollidable);
}

void CollisionManager::addCollidable(std::unique_ptr<Collidable> collidable)
{
	collidables.push_back(std::move(collidable));
	std::cout << "Collidables vector elements: " << collidables.size() << std::endl;
}