#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
//#include "Quadrant.h"
#include "Collidable.h"
#include "Ball.h"
#include "CollidableObjectType.h"

using namespace sf;

class CollidablesMap
{
//private:
//
//	float midX{ 0 };
//	float midY{ 0 };
//
//	std::vector<std::unique_ptr<Collidable>> collidablesVector;
//
//	std::unordered_map<Quadrant, std::vector<std::unique_ptr<Collidable>>> collidablesMap;
//
//	std::vector<Quadrant> getRelevantQuadrants(Quadrant mainQuadrant)
//	{
//		switch (mainQuadrant)
//		{
//		case Quadrant::TOP_LEFT:
//			return {
//				Quadrant::TOP_LEFT,
//				Quadrant::TOP_CENTRE,
//				Quadrant::LEFT_CENTRE,
//				Quadrant::CENTRE
//			};
//
//		case Quadrant::TOP_RIGHT:
//			return {
//				Quadrant::TOP_RIGHT,
//				Quadrant::TOP_CENTRE,
//				Quadrant::RIGHT_CENTRE,
//				Quadrant::CENTRE
//			};
//			
//		case Quadrant::BOTTOM_LEFT:
//			return {
//				Quadrant::BOTTOM_LEFT,
//				Quadrant::BOTTOM_CENTRE,
//				Quadrant::LEFT_CENTRE,
//				Quadrant::CENTRE
//			};
//
//		case Quadrant::BOTTOM_RIGHT:
//			return {
//				Quadrant::BOTTOM_RIGHT,
//				Quadrant::BOTTOM_CENTRE,
//				Quadrant::RIGHT_CENTRE,
//				Quadrant::CENTRE
//			};
//
//		default:
//			return {};
//		}
//	}
//
//	void calculateMidPoints(RenderWindow& window)
//	{
//		midX = window.getSize().x / 2.0f;
//		midY = window.getSize().y / 2.0f;
//	}
//
//	void setQuadrants(RenderWindow& window)
//	{
//		calculateMidPoints(window);
//
//		for (const auto& collidable : collidablesVector)
//		{
//			FloatRect spriteBounds = collidable->getSprite().getGlobalBounds();
//			Quadrant quadrant;
//
//			if (collidable->getCollidableObjectType() == CollidableObjectType::BRICK)
//			{
//				if (spriteBounds.top < midY && (spriteBounds.top + spriteBounds.height) < midY)
//				{
//					if (spriteBounds.left < midX && (spriteBounds.left + spriteBounds.width) < midX)
//						quadrant = Quadrant::TOP_LEFT;
//					else if (spriteBounds.left > midX && (spriteBounds.left + spriteBounds.width) > midX)
//						quadrant = Quadrant::TOP_RIGHT;
//					else if (spriteBounds.left < midX && (spriteBounds.left + spriteBounds.width) > midX)
//						quadrant = Quadrant::TOP_CENTRE;
//				}
//				else if (spriteBounds.top > midY && (spriteBounds.top + spriteBounds.height) > midY)
//				{
//					if (spriteBounds.left < midX && (spriteBounds.left + spriteBounds.width) < midX)
//						quadrant = Quadrant::BOTTOM_LEFT;
//					else if (spriteBounds.left > midX && (spriteBounds.left + spriteBounds.width) > midX)
//						quadrant = Quadrant::BOTTOM_RIGHT;
//					else if (spriteBounds.left < midX && (spriteBounds.left + spriteBounds.width) > midX)
//						quadrant = Quadrant::BOTTOM_CENTRE;
//				}
//				else if (spriteBounds.top < midY && (spriteBounds.top + spriteBounds.height) > midY)
//				{
//					if (spriteBounds.left < midX && (spriteBounds.left + spriteBounds.width) < midX)
//						quadrant = Quadrant::LEFT_CENTRE;
//					if (spriteBounds.left > midX && (spriteBounds.left + spriteBounds.width) > midX)
//						quadrant = Quadrant::RIGHT_CENTRE;
//					else if (spriteBounds.left < midX && (spriteBounds.left + spriteBounds.width) > midX)
//						quadrant = Quadrant::CENTRE;
//				}
//				else
//				{
//					std::cout << "ERROR DETERMINING A QUADRANT!" << std::endl;
//					return;
//				}
//			}
//			else
//				quadrant = Quadrant::BOTTOM_CENTRE; //platform
//
//			collidable->setQuadrant(quadrant);
//		}
//	}
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
