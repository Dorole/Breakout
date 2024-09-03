#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "events/HUDObserver.h"

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
	static std::map<std::size_t, std::string> levelsMap;
	std::vector<std::string> fileNamesVector =
	{
		"Level_1",
		"Level_2",
		"Level_3"
	};

	void mapLevelPathsToIndices();
	int currentLevel = 0;

	std::vector<HUDObserver*> levelObservers;

public:
	LevelLoader();

	void attachLevelObserver(HUDObserver* observer);
	bool nextLevelExists();
	void setLevel(LoadLevelMode mode);

	static std::map<std::size_t, std::string> getLevelsMap() { return levelsMap; }
	std::string& getFileName(int index) { return levelsMap[index]; }
	int getCurrentLevel() { return currentLevel; }

};

