#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cmath>
#include "BrickGridVisual.h"
#include "GameObject.h"
#include "Game.h"
#include "GridData.h"

BrickGridVisual::BrickGridVisual(Game& game, std::vector<std::vector<GridData>>& gridDataVectorRef)
	: GameObject(game), grid(game.getGrid()), gridDataVector(gridDataVectorRef)
{
	valueGetter.attachLevelDataObserver(this);
	init();

	registerForCollision();
	attachCollisionObservers(); //mozda bi se trebalo svaki put u initu? a colMan da ocisti vector?
}

void BrickGridVisual::init()
{
	columnCount = valueGetter.getColumnCount();
	rowCount = valueGetter.getRowCount();
	columnSpacing = valueGetter.getColumnSpacing();
	rowSpacing = valueGetter.getRowSpacing();
	topGridOffset = valueGetter.getGridOffset();
	leftGridOffset = getLeftRenderBorder();

	std::cout << "left grid offset: " << leftGridOffset << std::endl;

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

void BrickGridVisual::update(float deltaTime) { }

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

void BrickGridVisual::registerBrickCollidables()
{
	for (size_t row = 0; row < rowCount; row++)
	{
		for (size_t column = 0; column < columnCount; column++)
		{
			if (!gridDataVector[row][column].shouldRender) continue;

			collisionManager.addCollidable(std::make_unique<Collidable>(gridDataVector[row][column].getCollidable()));
		}
	}
}

void BrickGridVisual::registerForCollision()
{
	registerBrickCollidables();
}

void BrickGridVisual::attachCollisionObservers()
{
	for (size_t row = 0; row < rowCount; row++)
	{
		for (size_t column = 0; column < columnCount; column++)
		{
			if (!gridDataVector[row][column].shouldRender) continue;

			gridDataVector[row][column].attachCollisionObserver(collisionManager);
		}
	}
}


