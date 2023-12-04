#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "BrickGridVisual.h"
#include "GameObject.h"
#include "GridData.h"

BrickGridVisual::BrickGridVisual(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& brickGridRef, std::vector<std::vector<GridData>>& gridDataVectorRef)
	: window(windowRef), valueGetter(valueGetterRef), grid(brickGridRef), gridDataVector(gridDataVectorRef)
{
	valueGetter.attachLevelDataObserver(this);
	init();

}

void BrickGridVisual::init()
{
	columnCount = valueGetter.getColumnCount();
	rowCount = valueGetter.getRowCount();
	columnSpacing = valueGetter.getColumnSpacing();
	rowSpacing = valueGetter.getRowSpacing();

	grid.setGridOffset(getTopRenderBorder());
}

void BrickGridVisual::update(float deltaTime) { }

void BrickGridVisual::draw()
{
	for (size_t row = 0; row < rowCount; row++)
	{
		for (size_t column = 0; column < columnCount; column++)
		{
			if (!gridDataVector[row][column].shouldRender) continue;

			gridDataVector[row][column].setSpritePosition(
				Vector2f(
				column * (gridDataVector[row][column].getBrickSpriteBounds().width + columnSpacing),
				(row + gridOffset) * (gridDataVector[row][column].getBrickSpriteBounds().height + rowSpacing)));
				
			window.draw(gridDataVector[row][column].getBrickSprite());
		}
	}
}

void BrickGridVisual::onLevelChanged()
{
	init();
}

float BrickGridVisual::getTopRenderBorder()
{
	return (gridOffset * (gridDataVector[0][0].getBrickSpriteBounds().height + rowSpacing));
}



