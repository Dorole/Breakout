#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ValueGetter.h"
#include "BrickGrid.h"
#include "GameState.h"
#include "NumValueObserver.h"
#include "BrickObserver.h"


using namespace sf;

class Game : public NumValueObserver
{
private:
	RenderWindow& window;
	ValueGetter& valueGetter;
	BrickGrid& grid;

	std::shared_ptr<GameState> currentState;
	std::vector<NumValueObserver*> observers;

public:
	Game(RenderWindow& windowRef, ValueGetter& valueGetterRef, BrickGrid& grid);

	void changeStete(std::shared_ptr<GameState> newState);
	void handleInput();
	void update(float deltaTime);
	void draw();

	void attachObserver(NumValueObserver* observer);
	void onValueChanged(int value, ValueType valueType) override;
};


