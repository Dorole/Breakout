#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collidable.h"
#include "CollidableObjectType.h"
#include "CollidablesMap.h"
#include "CollisionObserver.h"

#include "EnumToStringConverter.h"

class CollisionManager
{
private:

	RenderWindow& window;
	CollidablesMap collidablesMap;
	EnumToStringConverter enumConverter;

	std::unique_ptr<Collidable> ballCollidable;
	std::vector<std::unique_ptr<Collidable>> collidables;

	std::vector<CollisionObserver*> collisionObservers;

	bool checkForCollision(Collidable& collidable)
	{		
		return ballCollidable->getSpriteGlobalBounds().intersects(collidable.getSpriteGlobalBounds());
	}

	void notifyCollisionObservers(Collidable& collidable)
	{
		for (const auto& observer : collisionObservers)
			observer->onCollision(collidable);
	}


public:
	CollisionManager(RenderWindow& windowRef) : window(windowRef), collidablesMap(windowRef) {};

	void update()
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
	
	void registerBallCollidable(std::unique_ptr<Collidable> ballCollidable);
	void addCollidable(std::unique_ptr<Collidable> collidable);
	void mapCollidables()
	{
		for (int i = 0; i < collidables.size(); i++)
		{
			auto& collidable = collidables.at(i);
			collidablesMap.mapCollidablePosition(*collidable);
		}
	}

	void attachCollisionObserver(CollisionObserver* observer)
	{
		collisionObservers.push_back(observer);
	}

	//ovo na pocetku svakog levela pozovi ili nek se ovaj subskrajba na event za novi level?
	void activateCollidables()
	{
		for (int i = 0; i < collidables.size(); i++)
			collidables.at(i)->setActiveStatus(true);
	}
};