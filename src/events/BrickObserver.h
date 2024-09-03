#pragma once

class Brick;

class BrickObserver
{
public:
	virtual void onBrickDestroyed(Brick& brick) = 0;
};

