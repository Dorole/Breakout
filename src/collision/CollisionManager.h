#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collidable.h"
#include "CollidableObjectType.h"
#include "CollidablesMap.h"
#include "events/CollisionObserver.h"
#include "utils/EnumToStringConverter.h"

class CollisionManager
{
private:
	RenderWindow& window;
	CollidablesMap collidablesMap;
	EnumToStringConverter enumConverter;

	std::unique_ptr<Collidable> ballCollidable;
	std::vector<std::unique_ptr<Collidable>> collidables;
	std::vector<CollisionObserver*> collisionObservers;

	bool checkForCollision(Collidable& collidable);
	void notifyCollisionObservers(Collidable& collidable);
	bool checkCollidableExists(Collidable& collidable);
	void deactivateCollidables(CollidableObjectType collidableType);
	void detachCollisionObservers();

public:
	CollisionManager(RenderWindow& windowRef) : window(windowRef), collidablesMap(windowRef) {};

	void registerBallCollidable(Collidable& ballCollidableRef);
	void addCollidable(Collidable& collidable);
	void mapCollidables();
	void attachCollisionObserver(CollisionObserver* observer);
	void update(float deltaTime);
	void activateCollision(Collidable& collidable);
	void handleLevelExit(CollidableObjectType collidableType);
	
};

