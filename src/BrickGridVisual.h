#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"
#include "ValueGetter.h"
#include "BrickGrid.h"
#include "GridData.h"
#include "LevelDataObserver.h"

class BrickGridVisual : public GameObject, public LevelDataObserver
{
private:
	RenderWindow& window;
	ValueGetter& valueGetter;
	BrickGrid& grid;
	int columnCount;
	int rowCount;
	int columnSpacing;
	int rowSpacing;
	
	int gridOffset = 6; //get from value getter/xml because the ball needs this too

	std::vector<std::vector<GridData>>& gridDataVector;

	float getTopRenderBorder();
	void init();

public:

	BrickGridVisual(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& brickGridRef, std::vector<std::vector<GridData>>& gridDataVectorRef);

	void update(float deltaTime) override;
	void draw() override;

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;
};

