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
	void mapCollidable(Collidable& collidable, SpritePosition pos)
	{
		auto& vec = collidablesMap[pos];
		vec.push_back(collidable);
	}



public:
	CollidablesMap(RenderWindow& window);


	std::vector<SpritePosition> getRelevantAreas(SpritePosition mainQuadrant);

	//pozvati iz collisionManagera
	//postavlja poziciju
	void mapCollidablePosition(Collidable& collidable) //promijeni naziv funkcije
	{
		if (collidable.getCollidableObjectType() == CollidableObjectType::PLATFORM)
		{
			SpritePosition platformPos = SpritePosition::BOTTOM_CENTRE;
			collidable.setSpritePosition(platformPos);
		}
		else
		{
			setCollidablePosition(collidable);
		}
		
		mapCollidable(collidable, collidable.getSpritePosition());
		
	}

	//za ball
	SpritePosition getCurrentPosition(Collidable& collidable)
	{
		Vector2f globalSpritePosition = collidable.getGlobalSpritePosition();
		SpritePosition position{ SpritePosition::TOP_LEFT };

		if (globalSpritePosition.x < midX)
		{
			if (globalSpritePosition.y < midY)
				position = SpritePosition::TOP_LEFT;
			else if (globalSpritePosition.y > midY)
				position = SpritePosition::BOTTOM_LEFT;
		}
		else if (globalSpritePosition.x > midX)
		{
			if (globalSpritePosition.y < midY)
				position = SpritePosition::TOP_RIGHT;
			else if (globalSpritePosition.y > midY)
				position = SpritePosition::BOTTOM_RIGHT;
		}

		return position;
	}

	std::unordered_map<SpritePosition, std::vector<Collidable>>& getMappedCollidables()
	{
		return collidablesMap;
	}

	void clearCollidablesMap()
	{
		for (auto& entry : collidablesMap) {
			entry.second.clear(); 
		}
	}

};
