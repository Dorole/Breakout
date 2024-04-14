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
	std::vector<CollisionObserver*> collisionObservers;//smart pointer ili nesto

	bool checkForCollision(Collidable& collidable);
	void notifyCollisionObservers(Collidable& collidable);

public:
	CollisionManager(RenderWindow& windowRef) : window(windowRef), collidablesMap(windowRef) {};

	void registerBallCollidable(Collidable& ballCollidableRef);
	void addCollidable(Collidable& collidable);
	void mapCollidables();
	void attachCollisionObserver(CollisionObserver* observer);
	void update();

	//ovo na pocetku svakog levela pozovi ili nek se ovaj subskrajba na event za novi level?
	void activateCollidables();
};