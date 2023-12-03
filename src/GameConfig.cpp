#include "GameConfig.h"
#include <map>
#include <vector>

GameConfig::GameConfig()
{
	mapLevelPathsToIndices();
}

std::map<int, std::string> GameConfig::levelsMap{};

void GameConfig::mapLevelPathsToIndices()
{
	for (size_t i = 0; i < fileNamesVector.size(); i++)
	{
		levelsMap[i] = fileNamesVector[i];
	}
}