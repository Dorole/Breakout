#include <iostream>
#include <vector>
#include "BrickGrid.h"
#include "ValueGetter.h"
#include "GridData.h"

#include "Brick.h"
#include "BrickSoft.h"
#include "BrickMedium.h"
#include "BrickHard.h"
#include "BrickImpenetrable.h"


BrickGrid::BrickGrid(ValueGetter& valueGetterRef)
	: valueGetter(valueGetterRef)
{
	bricksLayout = valueGetter.getBricksLayout();
	columnCount = valueGetter.getColumnCount();
	rowCount = valueGetter.getRowCount();

	setBrickSchemeVector();
	setGridDataVector();
}


void BrickGrid::setBrickSchemeVector()
{
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
	for (size_t i = 0; i < rowCount; i++)
	{
		gridDataVector.push_back(std::vector<GridData>());

		for (size_t j = 0; j < columnCount; j++)
		{
			GridData gridData;

			if (brickSchemeVector[i][j] == 'S')
				gridData.brickData = std::make_shared<BrickSoft>(valueGetter);
			else if (brickSchemeVector[i][j] == 'M')
				gridData.brickData = std::make_shared<BrickMedium>(valueGetter);
			else if (brickSchemeVector[i][j] == 'H')
				gridData.brickData = std::make_shared<BrickHard>(valueGetter);
			else if (brickSchemeVector[i][j] == 'I')
				gridData.brickData = std::make_shared<BrickImpenetrable>(valueGetter);
			else
				gridData.brickData = std::make_shared<BrickImpenetrable>(valueGetter); //PLACEHOLDER

			gridData.shouldRender = brickSchemeVector[i][j] != '_';

			gridDataVector[i].push_back(gridData);
		}
	}
}

void BrickGrid::handleCollision(std::size_t row, std::size_t column)
{
	gridDataVector[row][column].brickData->onHit();

	//uzas
	if (gridDataVector[row][column].shouldDestroy())
		gridDataVector[row][column].shouldRender = false;
}

bool BrickGrid::allBricksDestroyed()
{
	for (const auto& row : gridDataVector)
	{
		for (const auto& gridData : row)
		{
			if (gridData.shouldRender)
				return false;
		}
	}

	return true;

	//maybe event instead??
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

