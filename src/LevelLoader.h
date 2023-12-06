#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include "NumValueObserver.h"

enum class LoadLevelMode
{
	PROGRESS,
	RESET_LEVEL,
	RESET_GAME
};

using namespace sf;

class LevelLoader
{
private:
	static std::map<int, std::string> levelsMap;
	std::vector<std::string> fileNamesVector =
	{
		"Level_1",
		"Level_2",
		"Level_3"
	};

	void mapLevelPathsToIndices();
	int currentLevel = 0;

	std::vector<NumValueObserver*> levelObservers;

public:
	LevelLoader();

	void attachLevelObserver(NumValueObserver* observer);
	bool nextLevelExists();
	void setLevel(LoadLevelMode mode);

	static std::map<int, std::string> getLevelsMap() { return levelsMap; }
	std::string& getFileName(int index) { return levelsMap[index]; }
	int getCurrentLevel() { return currentLevel; }

};