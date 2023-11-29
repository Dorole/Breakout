#pragma once
#include <iostream> 
#include <vector>
#include "ValueGetter.h"
#include "GridData.h"
#include "Brick.h"
#include "BrickObserver.h"

class BrickGrid 
{
private:
	ValueGetter& valueGetter;
	int columnCount;
	int rowCount;
	std::string bricksLayout;

	std::vector<std::vector<char>> brickSchemeVector {};
	std::vector<std::vector<GridData>> gridDataVector {};

	std::vector<BrickObserver*> observers;

	/// <summary>
	/// Stores information in a 2d vector about brick id layout.
	/// </summary>
	void setBrickSchemeVector();

	/// <summary>
	/// Stores information about each grid cell - what brick is contained
	/// in it and whether it should be rendered.
	/// </summary>
	void setGridDataVector();

	//debug
	void printBrickScheme();


public:

	BrickGrid(ValueGetter& valueGetterRef);

	//make these const?
	std::vector<std::vector<char>> getBrickSchemeVector() { return brickSchemeVector; }
	std::vector<std::vector<GridData>>& getGridDataVector() { return gridDataVector; }

	void handleCollision(std::size_t row, std::size_t column);
	bool allBricksDestroyed();
	
	void attachObserver(BrickObserver* observer);

	//debug
	void setLevelFinished();

};

