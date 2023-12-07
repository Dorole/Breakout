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
	float verticalSpacing = 25;
	float fontSizePercentage = 7.0f;
	float textOffsetTopPercentage = 1.0f;
	float textOffsetSidePercentage = 10.0f;
	std::unique_ptr<Text> levelValueText;
	std::unique_ptr<Text> scoreValueText;
	std::unique_ptr<Text> currentLivesText;
	std::vector<std::unique_ptr<Text>> labelTexts;
	Vector2f adjustedScorePosition{};

	Color textColor = Color(0, 0, 102); //deep blue

public:

	UIManager(RenderWindow& windowRef, ValueGetter& valueGetterRef);

	void handleInput();
	void update();
	void draw();
	void setTextElements();

	// Inherited via NumValueObserver
	void onValueChanged(int value, ValueType valueType) override;

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;
};


