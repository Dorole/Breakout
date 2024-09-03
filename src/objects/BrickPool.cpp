#include "BrickPool.h"

#include <iostream>
#include <map>
#include <vector>
#include <stdexcept>

#include "Brick.h"
#include "BrickSoft.h"
#include "BrickMedium.h"
#include "BrickHard.h"
#include "BrickImpenetrable.h"

std::map<std::string, std::vector<GridData>> BrickPool::brickDataMap {};

BrickPool::BrickPool(ValueGetter& valueGetterRef, SoundPlayer& soundPlayerRef)
	: valueGetter(valueGetterRef), soundPlayer(soundPlayerRef)
{
	valueGetter.attachLevelDataObserver(this);
	valueGetter.attachInitReadyObserver(this);
}

void BrickPool::initBrickDataMap()
{
	for (const auto& id : valueGetter.getBricksIds())
	{
		std::vector<GridData> vec;
		int vecSize = reserveVectorSize(id);
		vec.reserve(vecSize);

		for (size_t i = 0; i < vecSize; i++)
		{
			vec.push_back(createGridData(id));
		}

		brickDataMap[id] = vec;
	}
}

int BrickPool::reserveVectorSize(std::string brickId)
{
	if (brickId == "S")
		return softBrickVectorSize;
	else if (brickId == "M" || brickId == "H")
		return defaultBrickVectorSize;
	else
		return impenetrableBrickVectorSize;
}

GridData BrickPool::createGridData(std::string id)
{
	GridData gridData;

	if (id == "S")
		gridData.brickData = std::make_shared<BrickSoft>(valueGetter, soundPlayer);
	else if (id == "M")
		gridData.brickData = std::make_shared<BrickMedium>(valueGetter, soundPlayer);
	else if (id == "H")
		gridData.brickData = std::make_shared<BrickHard>(valueGetter, soundPlayer);
	else if (id == "I")
		gridData.brickData = std::make_shared<BrickImpenetrable>(valueGetter, soundPlayer);

	gridData.shouldRender = false;
	gridData.canDestroy = id != "I";

	return gridData;
}

GridData BrickPool::getDataFromPool(std::string id)
{
	if (brickDataMap.find(id) != brickDataMap.end())
	{
		std::vector<GridData>& dataVec = brickDataMap[id];

		if (!dataVec.empty())
		{
			GridData gridData = dataVec.back();
			dataVec.pop_back();
			return gridData;
		}
		else
		{
			return createGridData(id);
		}

	}
	else
	{
		throw std::out_of_range("Key not found.");
	}
}

void BrickPool::returnDataToPool(GridData& gridData)
{
	std::string id = gridData.getBrickId();

	if (brickDataMap.find(id) != brickDataMap.end())
	{
		std::vector<GridData>& dataVec = brickDataMap[id];
		dataVec.push_back(gridData);
	}
	else
	{
		std::cerr << "! Key not found while returning data to pool !" << std::endl;
	}
}

void BrickPool::refreshPool()
{
	for (auto& pair : brickDataMap)
	{
		std::vector<GridData>& dataVec = pair.second;

		for (GridData& gridData : dataVec)
			gridData.brickData->reloadBrickValues(valueGetter, soundPlayer);
	}
}

void BrickPool::onLevelChanged()
{
	refreshPool();
}

void BrickPool::onInit()
{
	initBrickDataMap();
}

