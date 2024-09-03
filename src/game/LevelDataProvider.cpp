#include "LevelDataProvider.h"

void LevelDataProvider::registerPlatformData(GameObjectData& platformDataRef)
{
	auto platformDataPtr = std::make_unique<GameObjectData>(platformDataRef);
	platformData = std::move(platformDataPtr);
}

GameObjectData& LevelDataProvider::getPlatformData() const {

	if (platformData == nullptr)
		throw std::runtime_error("Platform data not registered");

	return *platformData;
}
