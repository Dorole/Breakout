#pragma once
#include <map>
#include <vector>
#include "ValueGetter.h"
#include "GridData.h"

class BrickPool
{
private:
	ValueGetter& valueGetter;

	//move to config and get from ctr
	const int softBrickVectorSize = 30;
	const int defaultBrickVectorSize = 20;
	const int impenetrableBrickVectorSize = 10;

	static std::map<std::string, std::vector<GridData>> brickDataMap;

	void initBrickDataMap();

	//should retrieve id strings from value getter (also in BrickGrid and bricks and wherever you need to use string id)!!!
	int reserveVectorSize(std::string brickId);
	GridData createGridData(std::string id);

public:

	BrickPool(ValueGetter& valueGetterRef);

	static std::map<std::string, std::vector<GridData>>& getBrickDataMap() { return brickDataMap; }

	GridData getDataFromPool(std::string id);
	void returnDataToPool(GridData& gridData);

	/// <summary>
	/// Load new values into bricks.
	/// </summary>
	//void refreshPool();

};
