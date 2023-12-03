#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include "NumValueObserver.h"

using namespace sf;

/// <summary>
/// Holder for global and const game members.
/// </summary>
class GameConfig
{
private:

	//Levels 
	static std::map<int, std::string> levelsMap;
	std::vector<std::string> fileNamesVector =
	{
		"Level_1",
		"Level_2",
		"Level_3"
	};

	void mapLevelPathsToIndices();
	std::vector<NumValueObserver*> levelObservers;


	//Game general
	int maxLives = 3; //make all static const?
	int currentLevel = 0;

	//Grid
	int gridOffset = 6;

	//UI 

	//Ball 
	Vector2f ballVelocity = Vector2f(-0.8f, -0.8f);
	float ballStartSpeed = 300.0f;
	float angleVariation = 0.2f;

	//Platform 


public:

	GameConfig();

	void attachLevelObserver(NumValueObserver* observer)
	{
		levelObservers.push_back(observer);
	}


	std::string& getFileName(int index) { return levelsMap[index]; }
	static std::map<int, std::string> getLevelsMap() { return levelsMap; }


	int getMaxLives() { return maxLives; }
	int getGridOffset() { return gridOffset; }
	Vector2f getBallVelocity() { return ballVelocity; }
	float getBallStartSpeed() { return ballStartSpeed; }
	float getAngleVariation() { return angleVariation; }

	bool nextLevelExists()
	{
		return (levelsMap.find(currentLevel + 1) != levelsMap.end());
	}

	void progressLevel()
	{
		currentLevel++;

		for (const auto& observer : levelObservers)
			observer->onValueChanged(currentLevel, ValueType::LEVEL);
	}

	int getCurrentLevel() { return currentLevel; }
};