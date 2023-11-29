#pragma once
#include "Brick.h"

class BrickObserver
{
public:
	virtual void onBrickDestroyed(Brick& brick) = 0;
};
