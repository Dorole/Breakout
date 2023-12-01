#pragma once
#include <iostream>
#include "Brick.h"
#include "ValueGetter.h"

class BrickImpenetrable : public Brick
{
private:


public:
	BrickImpenetrable(ValueGetter& valueGetter);

	void onHit() override;
	void reloadBrickValues(ValueGetter& valueGetter) override;
};

