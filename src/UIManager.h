#pragma once
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "TextCreator.h"
#include "Button.h"
#include "NumValueObserver.h"
#include "LevelDataObserver.h"

using namespace sf;

class UIManager : public NumValueObserver, public LevelDataObserver
{
private:
	RenderWindow& window;
	ValueGetter& valueGetter;
	
	TextCreator textCreator;
	Font font;
	unsigned int fontSize = 50;
	float verticalSpacing = 15;
	float textOffsetTop = 1;
	float textOffsetSide = 70;
	std::unique_ptr<Text> levelValueText;
	std::unique_ptr<Text> scoreValueText;
	std::unique_ptr<Text> currentLivesText;
	std::vector<std::unique_ptr<Text>> labelTexts;

	Texture fullHeartTex;
	Texture emptyHeartTex;
	Sprite emptyHeartSprite;
	Sprite fullHeartSprite;


public:

	UIManager(RenderWindow& windowRef, ValueGetter& valueGetterRef);

	void handleInput();
	void update();
	void draw();

	// Inherited via NumValueObserver
	void onValueChanged(int value, ValueType valueType) override;

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;
};


