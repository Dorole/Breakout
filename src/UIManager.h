#pragma once
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "Game.h"
#include "NumValueObserver.h"

using namespace sf;

class UIManager : public NumValueObserver
{
private:
	RenderWindow& window;
	ValueGetter& valueGetter;
	Game& game;
	
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
	
	enum class TextAlignment
	{
		TOP_LEFT,
		TOP_CENTER,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT
	};

	enum class TextOrigin
	{
		TOP_LEFT,
		TOP_RIGHT,
		TOP_CENTER
	};

	std::unique_ptr<Text> createNewText(Font& font, std::string textString, TextAlignment alignment, unsigned int charSize);
	std::unique_ptr<Text> createNewText(Font& font, std::string textString, Vector2f position, unsigned int charSize, TextOrigin txtOrigin = TextOrigin::TOP_LEFT);

	void setTextOrigin(TextOrigin origin, Text& text);

public:

	UIManager(RenderWindow& windowRef, ValueGetter& valueGetterRef, Game& gameRef);

	void update();
	void draw();

	void onValueChanged(int value, ValueType valueType) override;
};


