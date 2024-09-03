#include "LevelLoader.h"
#include <vector>
#include <iostream>

LevelLoader::LevelLoader()
{
	mapLevelPathsToIndices();
}

std::map<std::size_t, std::string> LevelLoader::levelsMap{};

void LevelLoader::mapLevelPathsToIndices()
{
	for (size_t i = 0; i < fileNamesVector.size(); i++)
	{
		levelsMap[i] = fileNamesVector[i];
	}
}

void LevelLoader::attachLevelObserver(HUDObserver* observer)
{
	levelObservers.push_back(observer);
}

bool LevelLoader::nextLevelExists()
{
	int nextLevel = currentLevel + 1;
	return (levelsMap.find(nextLevel) != levelsMap.end());
}

void LevelLoader::setLevel(LoadLevelMode mode)
{
	switch (mode)
	{
	case LoadLevelMode::PROGRESS:
		currentLevel++;
		break;
	case LoadLevelMode::RESET_LEVEL:
		break;
	case LoadLevelMode::RESET_GAME:
		currentLevel = 0;
		break;
	default:
		break;
	}

	for (const auto& observer : levelObservers)
		observer->onValueChanged(currentLevel, ValueType::LEVEL);

	std::cout << "Current level: " << currentLevel << std::endl;
}