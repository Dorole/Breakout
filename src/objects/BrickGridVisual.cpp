#include "BrickGridVisual.h"
#include <SFML/Window.hpp>
#include <cmath>

BrickGridVisual::BrickGridVisual(Game& game)
	: GameObject(game),
	grid(game.getGrid()),
	gridDataVector(game.getGrid().getGridDataVector())
{}

void BrickGridVisual::init()
{
	columnCount = valueGetter.getColumnCount();
	rowCount = valueGetter.getRowCount();
	columnSpacing = valueGetter.getColumnSpacing();
	rowSpacing = valueGetter.getRowSpacing();
	topGridOffset = valueGetter.getGridOffset();
	leftGridOffset = getLeftRenderBorder();
	grid.setGridOffset(getTopRenderBorder());
	setBrickSpritePositions();
}

void BrickGridVisual::setBrickSpritePositions()
{
	for (size_t row = 0; row < rowCount; row++)
	{
		for (size_t column = 0; column < columnCount; column++)
		{
			if (!gridDataVector[row][column].shouldRender) continue;

			gridDataVector[row][column].setSpritePosition(Vector2f(
				(column + leftGridOffset) * (gridDataVector[row][column].getBrickSpriteBounds().width + columnSpacing),
				(row + topGridOffset) * (gridDataVector[row][column].getBrickSpriteBounds().height + rowSpacing)));
		}
	}
}

void BrickGridVisual::update(float deltaTime) {}

void BrickGridVisual::draw()
{
	if (gridDataVector.size() < 1) return;

	for (size_t row = 0; row < rowCount; row++)
	{
		for (size_t column = 0; column < columnCount; column++)
		{
			if (!gridDataVector[row][column].shouldRender) continue;
			window.draw(gridDataVector[row][column].getBrickSprite());
		}
	}
}

float BrickGridVisual::getTopRenderBorder()
{
	return (topGridOffset * (gridDataVector[0][0].getBrickSpriteBounds().height + rowSpacing));
}

float BrickGridVisual::getLeftRenderBorder()
{
	float totalWidth = columnCount * (gridDataVector[0][0].getBrickSpriteBounds().width + columnSpacing) - columnSpacing;
	float leftOffset = (window.getSize().x - totalWidth) / 2.0f;

	leftOffset /= (gridDataVector[0][0].getBrickSpriteBounds().width) + columnSpacing;

	return std::max(leftOffset, 0.0f);
}



