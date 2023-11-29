#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"
#include "ValueGetter.h"
#include "BrickGrid.h"
#include "GridData.h"

class BrickGridVisual : public GameObject
{
private:
	RenderWindow& window;
	BrickGrid& grid;
	int columnCount;
	int rowCount;
	int columnSpacing;
	int rowSpacing;
	
	int gridOffset = 5; //get from value getter/xml because the ball needs this too

	std::vector<std::vector<GridData>>& gridDataVector;


public:

	BrickGridVisual(RenderWindow& windowRef, ValueGetter& valueGetter, BrickGrid& brickGridRef, std::vector<std::vector<GridData>>& gridDataVectorRef);

	void update(float deltaTime) override;
	void draw() override;

};

