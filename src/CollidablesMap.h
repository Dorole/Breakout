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
	
	void calculateMidPoints(RenderWindow& window);
	void setCollidablePosition(Collidable& collidable);

public:
	CollidablesMap(RenderWindow& window);

//	std::unordered_map<Quadrant, std::vector<std::unique_ptr<Collidable>>> collidablesMap;

	std::vector<SpritePosition> getRelevantAreas(SpritePosition mainQuadrant);

	void mapCollidablePosition(Collidable& collidable)
	{
		if (collidable.getCollidableObjectType() == CollidableObjectType::PLATFORM)
			collidable.setSpritePosition(SpritePosition::BOTTOM_CENTRE);
		else
			setCollidablePosition(collidable);
	}


//
//	void fillMap()
//	{
//		for (auto it = collidablesVector.begin(); it != collidablesVector.end(); ++it)
//		{
//			std::unique_ptr<Collidable>& collidable = *it;
//
//			Quadrant quadrant = collidable->getQuadrant();
//
//			std::vector<std::unique_ptr<Collidable>>& quadrantVector = collidablesMap[quadrant];
//			quadrantVector.emplace_back(std::move(collidable));
//
//			it = collidablesVector.erase(it);
//		}
//	}
//
//public:
//
//	void init(RenderWindow& window)
//	{
//		setQuadrants(window);
//		fillMap();
//	}
//
//	void addCollidableToVector(std::unique_ptr<Collidable> collidable)
//	{
//		collidablesVector.push_back(collidable);
//	}
//
//	void checkCollision(Ball& ball, Quadrant quadrant)
//	{
//		std::vector<Quadrant> relevantQuadrants = getRelevantQuadrants(quadrant);
//
//		for (const Quadrant& q : relevantQuadrants)
//		{
//			for (const auto& collidable : collidablesMap[q])
//			{
//				if (collidable->checkCollision(ball))
//				{
//					collidable->onCollision();
//					return;
//				}
//			}
//		}
//	}

};
