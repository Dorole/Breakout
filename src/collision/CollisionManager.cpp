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
	if (!checkCollidableExists(collidable))
		collidables.push_back(std::make_unique<Collidable>(collidable));
}

void CollisionManager::mapCollidables()
{
	collidablesMap.clearCollidablesMap();

	for (int i = 0; i < collidables.size(); i++)
	{
		auto& collidable = collidables.at(i);

		if (collidable->getActiveStatus())
			collidablesMap.mapCollidablePosition(*collidable);
	}
}

void CollisionManager::attachCollisionObserver(CollisionObserver* observer)
{
	collisionObservers.push_back(observer);
}


void CollisionManager::update(float deltaTime)
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

void CollisionManager::activateCollision(Collidable& collidable)
{
	collidable.setActiveStatus(true);
}


void CollisionManager::detachCollisionObservers()
{
	collisionObservers.clear();
}

void CollisionManager::deactivateCollidables(CollidableObjectType collidableType)
{
	for (int i = 0; i < collidables.size(); i++)
	{
		if (collidables.at(i)->getCollidableObjectType() == collidableType)
			collidables.at(i)->setActiveStatus(false);
	}
}

bool CollisionManager::checkCollidableExists(Collidable& collidable)
{
	for (const auto& existingCollidable : collidables)
	{
		if (existingCollidable->getId() == collidable.getId())
			return true;
	}

	return false;
}

void CollisionManager::handleLevelExit(CollidableObjectType collidableType)
{
	deactivateCollidables(collidableType);
	detachCollisionObservers();
}