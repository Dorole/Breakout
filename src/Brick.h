#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Brick 
{
protected:
	Sprite sprite;
	FloatRect spriteBounds;
	
	std::string id;
	Texture texture;
	int hitPoints;
	int breakScore;
	//audio

	enum class BrickType { SOFT, MEDIUM, HARD, IMPENETRABLE } brickType {BrickType::SOFT};
	//
	//BrickType convertCharToEnum(const char id)
	//{
	//	switch (id)
	//	{
	//	case 'S':
	//		brickType = BrickType::SOFT;
	//		break;
	//	case 'M':
	//		brickType = BrickType::MEDIUM;
	//		break;
	//	case 'H':
	//		brickType = BrickType::HARD;
	//	case 'I':
	//		brickType = BrickType::IMPENETRABLE;
	//		break;
	//	default:
	//		break;
	//	}
	//}

public:

	virtual void onHit() = 0;

};

