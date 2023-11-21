#pragma once
#include <iostream>
#include <vector>
#include "src/XmlParser.h"

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

	void getStringLayout(XmlParser& parser)
	{
		bricksLayout = parser.getTextFromNode("Level", "Bricks");
		bricksLayout.erase(std::remove_if(bricksLayout.begin(), bricksLayout.end(), ::isspace), bricksLayout.end());

		//debug
		std::cout << "Layout: " << bricksLayout << std::endl;
	}

	void setBrickSchemeVector()
	{
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

	BrickGrid(XmlParser& parser, const char* parentNode, const char* columnCountPath, const char* rowCountPath, const char* columnSpacingPath, const char* rowSpacingPath)
	{
		columnCount = parser.getNodeAttributeAsInt(columnCountPath, parentNode);
		rowCount = parser.getNodeAttributeAsInt(rowCountPath, parentNode);
		columnSpacing = parser.getNodeAttributeAsInt(columnSpacingPath, parentNode);
		rowSpacing = parser.getNodeAttributeAsInt(rowSpacingPath, parentNode);
		//ima li bolji nacin za ovo??

		getStringLayout(parser);
		setBrickSchemeVector();
		printBrickScheme();
	}

	std::vector<std::vector<char>> getBrickSchemeVector()
	{
		return brickSchemeVector;
	}

};

