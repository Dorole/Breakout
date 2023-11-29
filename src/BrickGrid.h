#pragma once
#include <iostream> 
#include <vector>
#include "ValueGetter.h"
#include "GridData.h"
#include "IObserver.h"

class BrickGrid //: public IObserver
{
private:
	ValueGetter& valueGetter;
	int columnCount;
	int rowCount;
	std::string bricksLayout;
	std::vector<std::vector<char>> brickSchemeVector {};
	std::vector<std::vector<GridData>> gridDataVector {};

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

	std::vector<std::vector<char>> getBrickSchemeVector() { return brickSchemeVector; }
	std::vector<std::vector<GridData>>& getGridDataVector() { return gridDataVector; }
	void handleCollision(std::size_t row, std::size_t column);
	bool allBricksDestroyed();
	
	//void onNotify() override;

	//debug
	void setLevelFinished();
};

