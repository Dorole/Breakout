#pragma once
#include <iostream>
#include "Brick.h"
#include "ValueGetter.h"

class BrickSoft : public Brick
{
private:


public:
	BrickSoft(ValueGetter& valueGetter);

	void onHit() override;
	void reloadBrickValues(ValueGetter& valueGetter) override;
};

