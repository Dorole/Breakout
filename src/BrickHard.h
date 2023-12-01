#pragma once
#include <iostream>
#include "Brick.h"
#include "ValueGetter.h"

class BrickHard : public Brick
{
private:


public:
	BrickHard(ValueGetter& valueGetter);

	void onHit() override;
	void reloadBrickValues(ValueGetter& valueGetter) override;
};

