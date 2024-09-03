#pragma once
#include "Brick.h"
#include "utils/ValueGetter.h"

class BrickSoft : public Brick
{
private:


public:
	BrickSoft(ValueGetter& valueGetter, SoundPlayer& soundPlayer);

	void onHit() override;
};



