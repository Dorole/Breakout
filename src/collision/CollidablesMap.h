#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "SpritePosition.h"
#include "Collidable.h"
#include "CollidableObjectType.h"

using namespace sf;

class CollidablesMap
{
private:

	float midX{ 0 };
	float midY{ 0 };

	std::unordered_map<SpritePosition, std::vector<Collidable>> collidablesMap;
	void calculateMidPoints(RenderWindow& window);
	void setCollidablePosition(Collidable& collidable);
	void mapCollidable(Collidable& collidable, SpritePosition pos);

public:
	CollidablesMap(RenderWindow& window);

	std::vector<SpritePosition> getRelevantAreas(SpritePosition mainQuadrant);
	void mapCollidablePosition(Collidable& collidable);
	SpritePosition getCurrentPosition(Collidable& collidable);
	void clearCollidablesMap();

	std::unordered_map<SpritePosition, std::vector<Collidable>>& getMappedCollidables() { return collidablesMap; }


};


