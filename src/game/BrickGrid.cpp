#include <iostream>
#include <vector>
#include "BrickGrid.h"


BrickGrid::BrickGrid(ValueGetter& valueGetterRef, BrickPool& brickPoolRef, CollisionManager& collisionManagerRef)
	: valueGetter(valueGetterRef), brickPool(brickPoolRef), collisionManager(collisionManagerRef)
{
	valueGetter.attachLevelDataObserver(this);
	valueGetter.attachInitReadyObserver(this);
}

void BrickGrid::init()
{
	bricksLayout = valueGetter.getBricksLayout();
	columnCount = valueGetter.getColumnCount();
	rowCount = valueGetter.getRowCount();

	setBrickSchemeVector();
	setGridDataVector();

	for (const auto& observer : initReadyObservers)
		observer->onInit();

	registerForCollision();
	observeBricks();
}

void BrickGrid::setBrickSchemeVector()
{
	brickSchemeVector.clear();

	bricksLayout.erase(std::remove_if(bricksLayout.begin(), bricksLayout.end(), ::isspace), bricksLayout.end());

	int index = 0;
	for (size_t i = 0; i < rowCount; i++)
	{
		brickSchemeVector.push_back(std::vector<char>());

		for (size_t j = 0; j < columnCount; j++)
		{
			brickSchemeVector.at(i).push_back(bricksLayout.at(index));
			index++;
		}
	}
}

void BrickGrid::setGridDataVector()
{
	gridDataVector.clear();

	for (size_t i = 0; i < rowCount; i++)
	{
		gridDataVector.push_back(std::vector<GridData>());

		for (size_t j = 0; j < columnCount; j++)
		{
			GridData gridData;

			if (brickSchemeVector[i][j] != '_')
			{
				gridData = brickPool.getDataFromPool(std::string(1, brickSchemeVector[i][j]));
			}
			else
				gridData = GridData{};

			gridData.shouldRender = brickSchemeVector[i][j] != '_';

			gridDataVector[i].push_back(gridData);
		}
	}
}

bool BrickGrid::allBricksDestroyed()
{
	for (const auto& row : gridDataVector)
	{
		for (const auto& gridData : row)
		{
			if (!gridData.canDestroy) continue;

			if (gridData.shouldRender)
				return false;
		}
	}

	//if level is cleared, return all gridData to pool
	for (auto& row : gridDataVector)
	{
		for (auto& gridData : row)
		{
			if (gridData.brickData != nullptr)
				brickPool.returnDataToPool(gridData);
			else
				gridData.~GridData();
		}

		row.clear();
	}

	return true;
}

void BrickGrid::attachGridObserver(BrickObserver* observer)
{
	gridObservers.push_back(observer);
}

void BrickGrid::registerForCollision()
{
	registerBrickCollidables();
	attachCollisionObservers();
}

void BrickGrid::registerBrickCollidables()
{
	for (size_t row = 0; row < rowCount; row++)
	{
		for (size_t column = 0; column < columnCount; column++)
		{
			if (!gridDataVector[row][column].shouldRender) continue;

			collisionManager.addCollidable(gridDataVector[row][column].getCollidable());
			collisionManager.activateCollision(gridDataVector[row][column].getCollidable());
		}
	}
}

void BrickGrid::attachCollisionObservers()
{
	for (size_t row = 0; row < rowCount; row++)
	{
		for (size_t column = 0; column < columnCount; column++)
		{
			if (!gridDataVector[row][column].shouldRender) continue;

			gridDataVector[row][column].attachCollisionObserver(collisionManager);
		}
	}
}

void BrickGrid::attachInitReadyObserver(InitReadyObserver* observer)
{
	initReadyObservers.push_back(observer);
}


void BrickGrid::setLevelFinished()
{
	for (auto& row : gridDataVector)
	{
		for (auto& gridData : row)
		{
			gridData.shouldRender = false;
		}
	}
}

void BrickGrid::onLevelChanged()
{
	init();
}

void BrickGrid::onBrickDestroyed(Brick& brick)
{
	updateGrid(brick);
}

void BrickGrid::onInit()
{
	init();
}

void BrickGrid::updateGrid(Brick& brick)
{
	for (auto& row : gridDataVector)
	{
		for (auto& gridData : row)
		{
			if (!gridData.canDestroy || !gridData.shouldRender) continue;

			if (gridData.shouldDestroy())
			{
				gridData.shouldRender = false;

				for (const auto& observer : gridObservers)
					observer->onBrickDestroyed(brick);

				return;
			}
		}
	}
}

void BrickGrid::observeBricks()
{
	for (const auto& row : gridDataVector)
	{
		for (const auto& gridData : row)
		{
			if (!gridData.canDestroy) continue;

			gridData.brickData->attachBrickObserver(this);
		}
	}
}


//************************** DEBUG FUNCTIONS **************************

void BrickGrid::printBrickScheme()
{
	for (const auto& row : brickSchemeVector)
	{
		for (char brick : row)
		{
			std::cout << brick << ' ';
		}
		std::cout << std::endl;
	}
}