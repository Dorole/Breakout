#pragma once
#include <iostream>
#include "GameObjectData.h"

class LevelDataProvider
{
private:
	float deathZone; //vjer ne treba - samo uzmi sprite i radi s tim
	
	
	//std::unique_ptr<GameObjectData> ballData;
	std::unique_ptr<GameObjectData> platformData;
	//std::unique_ptr<GameObjectData> brickVisualData;

public: 

	void registerPlatformData(std::unique_ptr<GameObjectData> platformDataRef)
	{
		platformData = std::move(platformDataRef);
	}

	GameObjectData& getPlatformData() const { 
		
		if (platformData == nullptr)
		{
			std::cout << "no platform data registered";
		}

		return *platformData; }


	float getDeathZone() const { return deathZone; }
	void setDeathZone(float value) { deathZone = value; }
};