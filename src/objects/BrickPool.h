#pragma once
#include <map>
#include <vector>
#include "audio/SoundPlayer.h"
#include "utils/ValueGetter.h"
#include "game/GridData.h"
#include "events/LevelDataObserver.h"
#include "events/InitReadyObserver.h"

class BrickPool : public LevelDataObserver, public InitReadyObserver
{
private:
	ValueGetter& valueGetter;
	SoundPlayer& soundPlayer;

	const int softBrickVectorSize = 30;
	const int defaultBrickVectorSize = 20;
	const int impenetrableBrickVectorSize = 20;

	static std::map<std::string, std::vector<GridData>> brickDataMap;

	void initBrickDataMap();

	int reserveVectorSize(std::string brickId);
	GridData createGridData(std::string id);

public:

	BrickPool(ValueGetter& valueGetterRef, SoundPlayer& soundPlayerRef);

	static std::map<std::string, std::vector<GridData>>& getBrickDataMap() { return brickDataMap; }
	GridData getDataFromPool(std::string id);
	void returnDataToPool(GridData& gridData);

	/// <summary>
	/// Load new values into bricks.
	/// </summary>
	void refreshPool();

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;

	// Inherited via InitReadyObserver
	virtual void onInit() override;

};


