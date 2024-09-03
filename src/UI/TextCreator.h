#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

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
	TOP_CENTER,
	CENTER
};



class TextCreator
{
private:
	float textOffsetTop;
	float textOffsetSide;


public:

	TextCreator();
	TextCreator(float topOffset, float sideOffset);

	std::unique_ptr<Text> createNewText(Font& font, std::string textString, Vector2f position, float charSize, TextOrigin txtOrigin = TextOrigin::TOP_LEFT);
	std::unique_ptr<Text> createNewText(RenderWindow& window, Font& font, std::string textString, TextAlignment alignment, float charSize);
	void setTextOrigin(TextOrigin origin, Text& text);

	void setTextOffsetTop(float value) { textOffsetTop = value; };
	void setTextOffsetSide(float value) { textOffsetSide = value; }
};

