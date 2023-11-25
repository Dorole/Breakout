#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "BrickGridVisual.h"
#include "GameObject.h"

BrickGridVisual::BrickGridVisual(RenderWindow& windowRef, ValueGetter& valueGetter, BrickGrid& brickGridRef)
	: window(windowRef), grid(brickGridRef)
{
	columnCount = valueGetter.getColumnCount();
	rowCount = valueGetter.getRowCount();
	columnSpacing = valueGetter.getColumnSpacing();
	rowSpacing = valueGetter.getRowSpacing();

	setBrickVector(valueGetter, grid);
	setSpriteVector();
}


void BrickGridVisual::update()
{
	//check the state of renderVector in BrickGrid
}

void BrickGridVisual::draw()
{
	for (size_t row = 0; row < rowCount; row++)
	{
		for (size_t column = 0; column < columnCount; column++)
		{

			if (!grid.getRenderVector().at(row).at(column)) continue;

			//bounds treba drugacije pohraniti da se ne retrievaju svaki frame 
			//potencijalno isto u vector ili mozda bolje map!
			spriteVector.at(row).at(column).setPosition(
				column * (brickVector.at(row).at(column)->getSpriteBounds().width + columnSpacing),
				row * (brickVector.at(row).at(column)->getSpriteBounds().height + rowSpacing));

			window.draw(spriteVector.at(row).at(column));
		}
	}
}


