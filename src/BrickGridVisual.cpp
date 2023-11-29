#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "BrickGridVisual.h"
#include "GameObject.h"
#include "GridData.h"

BrickGridVisual::BrickGridVisual(RenderWindow& windowRef, ValueGetter& valueGetter, BrickGrid& brickGridRef, std::vector<std::vector<GridData>>& gridDataVectorRef)
	: window(windowRef), grid(brickGridRef), gridDataVector(gridDataVectorRef)
{
	columnCount = valueGetter.getColumnCount();
	rowCount = valueGetter.getRowCount();
	columnSpacing = valueGetter.getColumnSpacing();
	rowSpacing = valueGetter.getRowSpacing();

	

}


void BrickGridVisual::update(float deltaTime)
{
	//gridDataVector = grid.getGridDataVector(); //ovo se ne bi trebalo updateati svaki frame, nego samo kad se brick unisti
}

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


