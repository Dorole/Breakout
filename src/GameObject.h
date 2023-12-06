#pragma once
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "LevelDataObserver.h"

using namespace sf;

class GameObject : public LevelDataObserver
{
protected:
	RenderWindow& window;
	ValueGetter& valueGetter;

public:
	GameObject(RenderWindow& windowRef, ValueGetter& valueGetterRef);

	virtual void init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0;

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;

};

