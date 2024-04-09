#pragma once
#include <iostream> 
#include <vector>
#include "ValueGetter.h"
#include "GridData.h"
#include "Brick.h"
#include "BrickObserver.h"
#include "BrickPool.h"
#include "LevelDataObserver.h"

class BrickGrid : public LevelDataObserver, public BrickObserver
{
private:
	ValueGetter& valueGetter;
	BrickPool& brickPool;
	int columnCount;
	int rowCount;
	std::string bricksLayout;

	std::vector<std::vector<char>> brickSchemeVector {};
	std::vector<std::vector<GridData>> gridDataVector {};

	std::vector<BrickObserver*> gridObservers;

	float gridOffset = 0;

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

	void init();
	void observeBricks();
	void updateGrid(Brick& brick);

public:

	BrickGrid(ValueGetter& valueGetterRef, BrickPool& brickPoolRef);

	//make these const?
	std::vector<std::vector<char>> getBrickSchemeVector() { return brickSchemeVector; }
	std::vector<std::vector<GridData>>& getGridDataVector() { return gridDataVector; }

	void handleCollision(std::size_t row, std::size_t column);
	bool allBricksDestroyed();

	void attachGridObserver(BrickObserver* observer);

	void setGridOffset(float value)
	{
		gridOffset = value;
	}

	float getGridOffset() { return gridOffset; }


	//debug
	void setLevelFinished();

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;


	// Inherited via BrickObserver
	virtual void onBrickDestroyed(Brick& brick) override;

};

