#pragma once
#include <SFML/Graphics.hpp>
#include "src/GameObject.h"

using namespace sf;

class Brick : public GameObject
{
protected:
	int hitPoints;
	int breakScore;
	//audio

	enum class BrickType { SOFT, MEDIUM, HARD, IMPENETRABLE } brickType {BrickType::SOFT};
	
	BrickType convertCharToEnum(const char id)
	{
		switch (id)
		{
		case 'S':
			brickType = BrickType::SOFT;
			break;
		case 'M':
			brickType = BrickType::MEDIUM;
			break;
		case 'H':
			brickType = BrickType::HARD;
		case 'I':
			brickType = BrickType::IMPENETRABLE;
			break;
		default:
			break;
		}
	}

public:
	//ctr
	virtual void onHit() = 0;

};

