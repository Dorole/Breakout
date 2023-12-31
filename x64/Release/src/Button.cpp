#include "Button.h"
#include <SFML/Graphics.hpp>
#include "SoundPlayer.h"

Button::Button(std::string txt, Vector2f size, Font& font, float fontSize, Color bgColor, Color textColor)
{
	text.setString(txt);
	text.setFillColor(textColor);
	text.setCharacterSize(static_cast<unsigned int>(fontSize));
	text.setFont(font);
	text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);

	button.setSize(size);
	button.setFillColor(bgColor); //USE TEXTURE INSTEAD?
	button.setOrigin(size.x / 2.0f, size.y / 2.0f);
}

void Button::setButtonOutline(float outlineThickness, Color outlineColor)
{
	button.setOutlineThickness(outlineThickness);
	button.setOutlineColor(outlineColor);
}

void Button::setButtonColor(Color color)
{
	button.setFillColor(color);
}

void Button::setButtonTransparency(AlphaChannel alphaChannel)
{
	Color buttonColor = button.getFillColor();
	float alpha = 255;

	switch (alphaChannel)
	{
	case AlphaChannel::OPAQUE:
		alpha = 255;
		break;
	case AlphaChannel::HALF_TRANSPARENT:
		alpha = 128;
		break;
	case AlphaChannel::TRANSPARENT:
		alpha = 0;
		break;
	default:
		break;
	}

	Color newColor = Color(buttonColor.r, buttonColor.g, buttonColor.b, static_cast<Uint8>(alpha));
	button.setFillColor(newColor);
}

void Button::setTextColor(Color color)
{
	text.setFillColor(color);
}

void Button::setButtonPosition(Vector2f position, Vector2f textOffset)
{
	button.setPosition(position);
	text.setPosition(button.getPosition() - textOffset);
}

Vector2f Button::getButtonPosition()
{
	return button.getPosition();
}

Vector2f Button::getButtonSize()
{
	return button.getSize();
}

bool Button::isMouseOverButton(RenderWindow& window)
{
	Vector2i mousePosition = Mouse::getPosition(window);
	Vector2f mouseWorldPosition = window.mapPixelToCoords(mousePosition);

	return button.getGlobalBounds().contains(mouseWorldPosition);
}

bool Button::buttonInteract(RenderWindow& window)
{
	if (isMouseOverButton(window))
	{
		setButtonTransparency(AlphaChannel::HALF_TRANSPARENT);

		if (!mouseOverButton)
		{
			soundPlayer.playRandomSound(SoundType::BUTTON);
			mouseOverButton = true;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			mouseOverButton = false;
			return true;
		}

		return false;
	}
	else
	{
		setButtonTransparency(AlphaChannel::OPAQUE);
		mouseOverButton = false;
		return false;
	}
}

void Button::drawButton(RenderWindow& window)
{
	window.draw(button);
	window.draw(text);
}