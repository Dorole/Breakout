#pragma once
#include <iostream>
#include "objects/GameObjectData.h"

/// <summary>
/// Currently only holds platform object data, 
/// but if necessary, can provide information on other game objects
/// </summary>
class LevelDataProvider
{
private:
	float deathZone; 
	std::unique_ptr<GameObjectData> platformData;

public:
	void registerPlatformData(GameObjectData& platformDataRef);
	GameObjectData& getPlatformData() const;

	float getDeathZone() const { return deathZone; }
	void setDeathZone(float value) { deathZone = value; }
};