#pragma once
#include "collision/Collidable.h"

class CollisionObserver
{
public:
	virtual void onCollision(Collidable& collidedObject) = 0;
};