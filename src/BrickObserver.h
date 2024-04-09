#pragma once
//#include "Brick.h"

class Brick;

class BrickObserver
{
public:
	virtual void onBrickDestroyed(Brick& brick) = 0;
};
