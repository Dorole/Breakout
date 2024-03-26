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
	CollisionManager(RenderWindow& windowRef) : window(windowRef), collidablesMap(windowRef)
	{	

	};

	void update()
	{
		SpritePosition ballPos = collidablesMap.getCurrentPosition(*ballCollidable); 
		auto relevantPositions = collidablesMap.getRelevantAreas(ballPos);

		for (const auto& position : relevantPositions)
		{
			auto mappedCollidables = collidablesMap.getMappedCollidables()[position];

			for (int i = 0; i < mappedCollidables.size(); i++)
			{
				if (checkForCollision(mappedCollidables.at(i)))
				{
					notifyCollisionObservers(mappedCollidables.at(i));
										
					//std::string collidableEnumName = enumConverter.spritePositionToString((mappedCollidables.at(i).getSpritePosition()));
					//std::string zoneEnumName = enumConverter.spritePositionToString(position);

					//std::cout << "Collision occured in " << zoneEnumName << "; with collidable position: " << collidableEnumName << std::endl;
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

			//std::string collidableTypeName = enumConverter.collidableTypeToString(collidable->getCollidableObjectType());
			//std::string collidableEnumName = enumConverter.spritePositionToString(collidable->getSpritePosition());
			//std::cout << "Collidable " << collidableTypeName << " mapped to " << collidableEnumName << std::endl;
		}
	}

	void attachCollisionObserver(CollisionObserver* observer)
	{
		collisionObservers.push_back(observer);
	}
};