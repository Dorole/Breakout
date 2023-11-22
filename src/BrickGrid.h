#pragma once
#include <iostream> //
#include <vector>
#include "ValueGetter.h"

//odvojiti ovo od renderanja? mozda onda odvoji Brick od GameObjecta 
//i umjesto toga BrickGridVisual : GameObject ? jer on ce crtati stvari? 
//a ovaj ce pratiti koliko jos ima brickova nerazbijenih
class BrickGrid
{
private:
	int columnCount;
	int rowCount;
	int columnSpacing;
	int rowSpacing;
	std::string bricksLayout;
	std::vector<std::vector<char>> brickSchemeVector;

	void setBrickSchemeVector()
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

	//debug
	void printBrickScheme()
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


public:

	BrickGrid(ValueGetter& valueGetter)
	{
		columnCount = valueGetter.getColumnCount();
		rowCount = valueGetter.getRowCount();
		columnSpacing = valueGetter.getColumnSpacing();
		rowSpacing = valueGetter.getRowSpacing();

		bricksLayout = valueGetter.getBricksLayout();

		setBrickSchemeVector();
		printBrickScheme();
	}

	std::vector<std::vector<char>> getBrickSchemeVector()
	{
		return brickSchemeVector;
	}

};

