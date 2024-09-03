#pragma once
#include "Brick.h"
#include "utils/ValueGetter.h"

class BrickMedium : public Brick
{
private:


public:
	BrickMedium(ValueGetter& valueGetter, SoundPlayer& soundPlayer);

	void onHit() override;
};



