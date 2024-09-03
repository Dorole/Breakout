#include "Button.h"

Button::Button(SoundPlayer& soundPlayerRef) : soundPlayer(soundPlayerRef)
{}

void Button::configureButton(const Vector2f size, const Font& font, const float fontSize, const Color bgColor, const Color textColor)
{
	configureButtonText(font, fontSize, textColor);
	configureButtonDesign(size, bgColor);
}

void Button::configureButton(const std::string txt, const Vector2f size, const Font& font, const float fontSize, const Color bgColor, const Color textColor)
{
	setButtonText(txt);
	configureButton(size, font, fontSize, bgColor, textColor);
}

void Button::configureButtonDesign(const Vector2f size, const Color bgColor)
{
	button.setSize(size);
	button.setFillColor(bgColor);
	button.setOrigin(size.x / 2.0f, size.y / 2.0f);
}

void Button::configureButtonText(const Font& font, const float fontSize, const Color textColor)
{
	text.setFillColor(textColor);
	text.setCharacterSize(static_cast<unsigned int>(fontSize));
	text.setFont(font);
	text.setOrigin(text.getLocalBounds().width / 2.0f, text.getLocalBounds().height / 2.0f);
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

void Button::setButtonText(const std::string txt)
{
	text.setString(txt);
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
	if (!isVisible) return false;

	Vector2i mousePosition = Mouse::getPosition(window);
	Vector2f mouseWorldPosition = window.mapPixelToCoords(mousePosition);

	return button.getGlobalBounds().contains(mouseWorldPosition);
}

bool Button::buttonInteract(RenderWindow& window, sf::Event& event)
{
	if (isMouseOverButton(window))
	{
		setButtonTransparency(AlphaChannel::HALF_TRANSPARENT);

		if (!mouseOverButton)
		{
			soundPlayer.playRandomSound(SoundType::BUTTON);
			mouseOverButton = true;
		}

		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
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

void Button::setVisibility(bool visible)
{
	isVisible = visible;
}