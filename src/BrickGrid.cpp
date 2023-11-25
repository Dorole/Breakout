#include <iostream>
#include <vector>
#include "BrickGrid.h"
#include "ValueGetter.h"


BrickGrid::BrickGrid(ValueGetter& valueGetter)
{
	bricksLayout = valueGetter.getBricksLayout();
	columnCount = valueGetter.getColumnCount();
	rowCount = valueGetter.getRowCount();

	setBrickSchemeVector();
	setRenderVector();
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

void BrickGrid::setRenderVector()
{
	for (size_t i = 0; i < rowCount; i++)
	{
		renderVector.push_back(std::vector<bool>());

		for (size_t j = 0; j < columnCount; j++)
		{
			if (brickSchemeVector[i][j] != '_')
				renderVector.at(i).push_back(true);
			else
				renderVector.at(i).push_back(false);
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


void BrickGrid::printRenderVector()
{
	for (const auto& row : renderVector)
	{
		for (const auto& val : row)
		{
			if (val)
				std::cout << "T" << ' ';
			else
				std::cout << "F" << ' ';
		}
		std::cout << std::endl;
	}
}
