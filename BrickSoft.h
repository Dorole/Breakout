#pragma once
#include "src/Brick.h"
#include "src/ValueGetter.h"

class BrickSoft : Brick
{
private:


public:
	BrickSoft(ValueGetter& valueGetter)
	{
		
	}


	void onHit() override;
};

