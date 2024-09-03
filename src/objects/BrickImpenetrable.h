#pragma once
#include "Brick.h"
#include "utils/ValueGetter.h"

class BrickImpenetrable : public Brick
{
private:


public:
	BrickImpenetrable(ValueGetter& valueGetter, SoundPlayer& soundPlayer);

	void onHit() override;
};



