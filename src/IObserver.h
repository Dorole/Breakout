#pragma once
#include "Brick.h"

class IObserver
{
public:
	virtual void onNotify() = 0;
};
