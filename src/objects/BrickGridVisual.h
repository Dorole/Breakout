#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"
#include "game/Game.h"
#include "game/BrickGrid.h"
#include "game/GridData.h"
#include "utils/ValueGetter.h"

using namespace sf;

class BrickGridVisual : public GameObject
{
private:

	// ************************* REFERENCES *************************
	BrickGrid& grid;
	std::vector<std::vector<GridData>>& gridDataVector;

	// ************************* PRIVATE STATE ************************
	int columnCount{ 0 };
	int rowCount{ 0 };
	int columnSpacing{ 0 };
	int rowSpacing{ 0 };
	int topGridOffset{ 0 };
	float leftGridOffset{ 0 };

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

	BrickGridVisual(Game& game);

	void setBrickSpritePositions();

	// inherited via GameObject
	void init() override;
	void update(float deltaTime) override;
	void draw() override;
};


