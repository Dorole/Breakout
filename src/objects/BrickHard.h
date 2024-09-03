#pragma once
#include "Brick.h"
#include "utils/ValueGetter.h"

class BrickHard : public Brick
{
private:


public:
	BrickHard(ValueGetter& valueGetter, SoundPlayer& soundPlayer);

	void onHit() override;
};



