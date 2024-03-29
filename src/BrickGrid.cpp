#include <iostream>
#include <vector>
#include "BrickGrid.h"
#include "ValueGetter.h"
#include "GridData.h"
#include "BrickPool.h"
#include "BrickObserver.h"


BrickGrid::BrickGrid(ValueGetter& valueGetterRef, BrickPool& brickPoolRef)
	: valueGetter(valueGetterRef), brickPool(brickPoolRef)
{
	valueGetter.attachLevelDataObserver(this);
	init();
}

void BrickGrid::init()
{
	bricksLayout = valueGetter.getBricksLayout();
	columnCount = valueGetter.getColumnCount();
	rowCount = valueGetter.getRowCount();

	setBrickSchemeVector();
	setGridDataVector();
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

//PROBLEM!!!
void BrickGrid::handleCollision(std::size_t row, std::size_t column)
{
	if (gridDataVector[row][column].shouldDestroy())
	{
		gridDataVector[row][column].shouldRender = false;

		for (const auto& observer : observers)
			observer->onBrickDestroyed(*gridDataVector[row][column].brickData);	
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

void BrickGrid::attachObserver(BrickObserver* observer)
{
	observers.push_back(observer);
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

