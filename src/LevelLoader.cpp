#include "LevelLoader.h"
#include <map>
#include <vector>
#include "NumValueObserver.h"

LevelLoader::LevelLoader()
{
	mapLevelPathsToIndices();
}

std::map<int, std::string> LevelLoader::levelsMap{};

void LevelLoader::mapLevelPathsToIndices()
{
	for (size_t i = 0; i < fileNamesVector.size(); i++)
	{
		levelsMap[i] = fileNamesVector[i];
	}
}

void LevelLoader::attachLevelObserver(NumValueObserver* observer)
{
	levelObservers.push_back(observer);
}

bool LevelLoader::nextLevelExists()
{
	return (levelsMap.find(currentLevel + 1) != levelsMap.end());
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
}