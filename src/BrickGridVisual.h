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
	std::vector<std::vector<std::unique_ptr<Brick>>> brickVector {};
	
	void setBrickVector(ValueGetter& valueGetter, BrickGrid& grid)
	{
		std::vector<std::vector<char>> brickSchemeVector = grid.getBrickSchemeVector();

		for (size_t i = 0; i < rowCount; i++)
		{
			brickVector.push_back(std::vector<std::unique_ptr<Brick>>());

			for (size_t j = 0; j < columnCount; j++)
			{
				if (brickSchemeVector[i][j] == 'S')
					brickVector.at(i).push_back(std::make_unique<BrickSoft>(valueGetter));
				else if (brickSchemeVector[i][j] == 'M')
					brickVector.at(i).push_back(std::make_unique<BrickMedium>(valueGetter));
				else if (brickSchemeVector[i][j] == 'H')
					brickVector.at(i).push_back(std::make_unique<BrickHard>(valueGetter));
				else if (brickSchemeVector[i][j] == 'I')
					brickVector.at(i).push_back(std::make_unique<BrickImpenetrable>(valueGetter));
				else
					brickVector.at(i).push_back(std::make_unique<BrickHard>(valueGetter)); //PLACEHOLDER! SMISLI STO OVDJE

			}
		}
	}


	std::vector<std::vector<Sprite>> spriteVector;
	void setSpriteVector()
	{
		for (size_t i = 0; i < rowCount; i++)
		{
			spriteVector.push_back(std::vector<Sprite>());

			for (size_t j = 0; j < columnCount; j++)
			{
				spriteVector.at(i).push_back(brickVector[i][j]->getSprite());
			}
		}
	}

public:

	BrickGridVisual(RenderWindow& windowRef, ValueGetter& valueGetter, BrickGrid& brickGridRef);

	void update(float deltaTime) override;
	void draw() override;

};

