#pragma once
#include <iostream>
#include "Brick.h"
#include "ValueGetter.h"
#include "BrickTypeValues.h"

class BrickSoft : Brick
{
private:


public:
	BrickSoft(ValueGetter& valueGetter)
	{
		BrickTypeValues values = valueGetter.getBrickValuesById("S");

		id = values.id;
		hitPoints = values.hitPoints;
		breakScore = values.breakScore;
		
		texture.loadFromFile(values.texture);
		sprite.setTexture(texture);

		//audio
	}


	void onHit() override
	{

	};
};

