#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"
#include "BrickGrid.h"
#include "Brick.h"
#include "BrickSoft.h"
#include "BrickMedium.h"
#include "BrickHard.h"
#include "BrickImpenetrable.h"
#include "ValueGetter.h"

class BrickGridVisual : public GameObject
{
private:
	RenderWindow& window;
	BrickGrid& grid;
	int columnCount;
	int rowCount;
	int columnSpacing;
	int rowSpacing;

	//ovo mozda ima vise smisla da bude u BrickGrid?
	//je li potrebno uopce??
	std::vector<std::vector<Brick*>> brickVector;
	void setBrickVector(ValueGetter& valueGetter, BrickGrid& grid)
	{
		std::vector<std::vector<char>> brickSchemeVector = grid.getBrickSchemeVector();

		for (size_t i = 0; i < rowCount; i++)
		{
			brickVector.push_back(std::vector<Brick*>());

			for (size_t j = 0; j < columnCount; j++)
			{
				switch (brickSchemeVector.at(i).at(j))
				{
				case 'S':
					brickVector.at(i).push_back(new BrickSoft(valueGetter));
					break;
				case 'M':
					brickVector.at(i).push_back(new BrickMedium(valueGetter));
					break;
				case 'H':
					brickVector.at(i).push_back(new BrickHard(valueGetter));
					break;
				case 'I':
					brickVector.at(i).push_back(new BrickImpenetrable(valueGetter));
					break;
				case '_':
					break;
				default:
					break;
				}

			}
		}
	}


	std::vector<std::vector<Sprite>> spriteVector;
	void setSpriteVector()
	{
		for (size_t i = 0; i < columnCount; i++)
		{
			spriteVector.push_back(std::vector<Sprite>());

			for (size_t j = 0; j < rowCount; j++)
			{
				spriteVector.at(i).push_back(brickVector[i][j]->getSprite());
			}
		}
	}

public:

	BrickGridVisual(RenderWindow& windowRef, ValueGetter& valueGetter, BrickGrid& brickGridRef)
		: window(windowRef), grid(brickGridRef)
	{
		columnCount = valueGetter.getColumnCount();
		rowCount = valueGetter.getRowCount();
		columnSpacing = valueGetter.getColumnSpacing();
		rowSpacing = valueGetter.getRowSpacing();

		setBrickVector(valueGetter, grid);
		setSpriteVector();
	}

	void update() override;
	void draw() override
	{
		//for (size_t i = 0; i < columnCount; i++)
		//{
		//	for (size_t j = 0; j < rowCount; j++)
		//	{
		//		//bounds treba drugacije pohraniti da se ne retrievaju svaki frame 
		//		//potencijalno isto u vector ili mozda bolje map!
		//		spriteVector.at(i).at(j).setPosition(
		//			i * (brickVector.at(i).at(j)->getSpriteBounds().width + columnSpacing),
		//			j * (brickVector.at(i).at(j)->getSpriteBounds().height + rowSpacing));

		//		window.draw(spriteVector.at(i).at(j));
		//	}
		//}
	}

};

