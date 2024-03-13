#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Quadrant.h"
#include "CollidableObjectType.h"


using namespace sf;

class Collidable
{
private:
	CollidableObjectType objectType = CollidableObjectType::BRICK;
	Quadrant quadrant = Quadrant::TOP_LEFT;

public:

	Collidable(CollidableObjectType collidableType);

	virtual void onCollision() = 0;
	virtual const Sprite& getSprite() const = 0;

	bool checkCollision(Ball& ball);
	CollidableObjectType getCollidableObjectType() { return objectType; }
	void setQuadrant(Quadrant q);
	Quadrant getQuadrant() { return quadrant; }

};

