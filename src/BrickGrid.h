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
	std::vector<std::vector<bool>> renderVector;

	/// <summary>
	/// Stores information in a 2d vector about brick id layout.
	/// </summary>
	void setBrickSchemeVector();

	/// <summary>
	/// Stores information in a 2d vector about whether or not 
	/// a brick should be rendered in the grid.
	/// </summary>
	void setRenderVector();

	//debug
	void printBrickScheme();

	//debug
	void printRenderVector();


public:

	BrickGrid(ValueGetter& valueGetter);

	std::vector<std::vector<char>> getBrickSchemeVector() { return brickSchemeVector; }
	std::vector<std::vector<bool>> getRenderVector() { return renderVector; }

};

