#pragma once
#include <SFML/Graphics.hpp>
#include "audio/SoundPlayer.h"

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

	SoundPlayer& soundPlayer;
	bool mouseOverButton = false;
	bool isVisible = true;

public:
	Button(SoundPlayer& soundPlayerRef);

	void configureButton(const Vector2f size, const Font& font, const float fontSize, const Color bgColor, const Color textColor);
	void configureButton(const std::string txt, const Vector2f size, const Font& font, const float fontSize, const Color bgColor, const Color textColor);
	void configureButtonDesign(const Vector2f size, const Color bgColor);
	void configureButtonText(const Font& font, const float fontSize, const Color textColor);
	void setButtonOutline(float outlineThickness, Color outlineColor);
	void setButtonColor(Color color);
	void setButtonTransparency(AlphaChannel alphaChannel);
	void setButtonText(const std::string txt);
	void setTextColor(Color color);
	void setButtonPosition(Vector2f position, Vector2f textOffset);
	Vector2f getButtonPosition();
	Vector2f getButtonSize();

	void setVisibility(bool visibile);
	bool getVisibility() { return isVisible; }
	bool isMouseOverButton(RenderWindow& window);
	bool buttonInteract(RenderWindow& window, sf::Event& event);
	void drawButton(RenderWindow& window);
};


