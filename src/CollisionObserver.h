#pragma once
#include "CollidableObjectType.h"
#include "Collidable.h"

class CollisionObserver 
{
public:
	virtual void onCollision(Collidable& collidedObject) = 0;
};