#pragma once
#include "Brick.h"

class Observer
{
public:
	virtual void onNotify() = 0;
};
