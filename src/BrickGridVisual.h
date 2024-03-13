#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"
#include "Game.h"
#include "ValueGetter.h"
#include "BrickGrid.h"
#include "GridData.h"

using namespace sf;

class BrickGridVisual : public GameObject
{
private:

	// ************************* REFERENCES *************************
	BrickGrid& grid;
	std::vector<std::vector<GridData>>& gridDataVector;

	// ************************* PRIVATE STATE ************************
	int columnCount;
	int rowCount;
	int columnSpacing;
	int rowSpacing;	
	int topGridOffset;
	float leftGridOffset;

	// ************************* PRIVATE FUNCTIONS ************************
	/// <summary>
	/// Defines how low from the window's top border
	/// the first row of bricks should be rendered.
	/// </summary>
	float getTopRenderBorder();

	/// <summary>
	/// Defines where the first column should be drawn
	/// so that the grid is centerd in the window.
	/// </summary>
	float getLeftRenderBorder();


	// ************************* PUBLIC FUNCTIONS ************************
public:

	BrickGridVisual(Game& game, std::vector<std::vector<GridData>>& gridDataVectorRef);

	// inherited via GameObject
	void init() override;
	void update(float deltaTime) override;
	void draw() override;
};

