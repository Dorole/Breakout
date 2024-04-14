#include "CollisionManager.h"

bool CollisionManager::checkForCollision(Collidable& collidable)
{
	return ballCollidable->getSpriteGlobalBounds().intersects(collidable.getSpriteGlobalBounds());
}

void CollisionManager::notifyCollisionObservers(Collidable& collidable)
{
	for (const auto& observer : collisionObservers)
		observer->onCollision(collidable);
}

void CollisionManager::registerBallCollidable(Collidable& ballCollidableRef)
{	
	if (ballCollidableRef.getCollidableObjectType() != CollidableObjectType::BALL)
	{
		std::cerr << "ERROR: Tried to register something other than Ball Collidable as Ball Collidable!" << std::endl;
		return;
	}

	auto ballCollidablePtr = std::make_unique<Collidable>(ballCollidableRef);
	ballCollidable = std::move(ballCollidablePtr);
}

void CollisionManager::addCollidable(Collidable& collidable)
{
	auto collidablePtr = std::make_unique<Collidable>(collidable);
	collidables.push_back(std::move(collidablePtr));
}

void CollisionManager::mapCollidables()
{
	for (int i = 0; i < collidables.size(); i++)
	{
		auto& collidable = collidables.at(i);
		collidablesMap.mapCollidablePosition(*collidable);
	}
}

void CollisionManager::attachCollisionObserver(CollisionObserver* observer)
{
	collisionObservers.push_back(observer);
}

void CollisionManager::activateCollidables()
{
	for (int i = 0; i < collidables.size(); i++)
		collidables.at(i)->setActiveStatus(true);
}

void CollisionManager::update()
{
	SpritePosition ballPos = collidablesMap.getCurrentPosition(*ballCollidable);
	auto relevantPositions = collidablesMap.getRelevantAreas(ballPos);

	for (const auto& position : relevantPositions)
	{
		auto& mappedCollidables = collidablesMap.getMappedCollidables()[position];

		for (int i = 0; i < mappedCollidables.size(); i++)
		{
			if (mappedCollidables.at(i).getActiveStatus() && checkForCollision(mappedCollidables.at(i)))
			{
				notifyCollisionObservers(mappedCollidables.at(i));
				return;
			}

		}
	}
}