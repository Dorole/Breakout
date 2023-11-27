#pragma once
#include <iostream>
#include "Brick.h"
#include "ValueGetter.h"

class BrickMedium : public Brick
{
private:


public:
	BrickMedium(ValueGetter& valueGetter);

	void onHit() override;
};

