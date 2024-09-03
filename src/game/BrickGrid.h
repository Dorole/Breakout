#pragma once
#include <iostream> 
#include <vector>
#include "GridData.h"
#include "utils/ValueGetter.h"
#include "objects/Brick.h"
#include "objects/BrickPool.h"
#include "collision/CollisionManager.h"
#include "events/LevelDataObserver.h"
#include "events/BrickObserver.h"
#include "events/InitReadyObserver.h"

class BrickGrid : public LevelDataObserver, public BrickObserver, public InitReadyObserver
{
private:
	ValueGetter& valueGetter;
	BrickPool& brickPool;
	CollisionManager& collisionManager;

	int columnCount{ 0 };
	int rowCount{ 0 };
	std::string bricksLayout = "";

	std::vector<std::vector<char>> brickSchemeVector {};
	std::vector<std::vector<GridData>> gridDataVector {};

	std::vector<BrickObserver*> gridObservers;
	std::vector<InitReadyObserver*> initReadyObservers;

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

	void registerBrickCollidables();
	void attachCollisionObservers();

public:

	BrickGrid(ValueGetter& valueGetterRef, BrickPool& brickPoolRef, CollisionManager& collisionManagerRef);

	std::vector<std::vector<char>> getBrickSchemeVector() const { return brickSchemeVector; }
	std::vector<std::vector<GridData>>& getGridDataVector() { return gridDataVector; }

	void setGridOffset(float value) { gridOffset = value; }
	float getGridOffset() { return gridOffset; }

	bool allBricksDestroyed();
	void attachGridObserver(BrickObserver* observer);
	void attachInitReadyObserver(InitReadyObserver* observer);
	void registerForCollision();

	//debug
	void setLevelFinished();

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;

	// Inherited via BrickObserver
	virtual void onBrickDestroyed(Brick& brick) override;

	// Inherited via InitReadyObserver
	virtual void onInit() override;

};



