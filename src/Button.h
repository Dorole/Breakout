#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum class AlphaChannel
{
	OPAQUE,
	HALF_TRANSPARENT,
	TRANSPARENT
};

class Button
{
private:
	RectangleShape button;
	Text text;

public:
	Button() {}

	Button(std::string txt, Vector2f size, Font& font, int fontSize, Color bgColor, Color textColor);

	void setButtonOutline(float outlineThickness, Color outlineColor);
	void setButtonColor(Color color);
	void setButtonTransparency(AlphaChannel alphaChannel);
	void setTextColor(Color color);
	void setButtonPosition(Vector2f position, Vector2f textOffset);
	Vector2f getButtonPosition();
	Vector2f getButtonSize();

	bool isMouseOverButton(RenderWindow& window);
	bool buttonInteract(RenderWindow& window);
	void drawButton(RenderWindow& window);
};
