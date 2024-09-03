#include "TextCreator.h"

TextCreator::TextCreator()
	: textOffsetTop(0), textOffsetSide(0)
{}

TextCreator::TextCreator(float topOffset, float sideOffset)
	: textOffsetTop(topOffset), textOffsetSide(sideOffset)
{}

std::unique_ptr<Text> TextCreator::createNewText(RenderWindow& window, Font& font, std::string textString, TextAlignment alignment, float charSize)
{
	auto text = std::make_unique<Text>();

	text->setFont(font);
	text->setString(textString);
	text->setCharacterSize(static_cast<unsigned int>(charSize));

	Vector2f textPosition;
	switch (alignment)
	{
	case TextAlignment::TOP_LEFT:
		setTextOrigin(TextOrigin::TOP_CENTER, *text);
		textPosition = Vector2f(textOffsetSide, textOffsetTop);
		break;
	case TextAlignment::TOP_RIGHT:
		setTextOrigin(TextOrigin::TOP_CENTER, *text);
		textPosition = Vector2f(window.getSize().x - textOffsetSide, textOffsetTop);
		break;
	case TextAlignment::TOP_CENTER:
		setTextOrigin(TextOrigin::TOP_CENTER, *text);
		textPosition = Vector2f(window.getSize().x / 2.0f, textOffsetTop);
		break;
	default:
		break;
	}

	text->setPosition(textPosition);

	return text;
}

std::unique_ptr<Text> TextCreator::createNewText(Font& font, std::string textString, Vector2f position, float charSize, TextOrigin txtOrigin)
{
	auto text = std::make_unique<Text>();

	text->setFont(font);
	text->setString(textString);
	text->setCharacterSize(static_cast<unsigned int>(charSize));
	setTextOrigin(txtOrigin, *text);
	text->setPosition(position);

	return text;
}


void TextCreator::setTextOrigin(TextOrigin origin, Text& text)
{
	auto textBounds = text.getLocalBounds();

	switch (origin)
	{
	case TextOrigin::TOP_LEFT:
		text.setOrigin(textBounds.left, 0);
		break;
	case TextOrigin::TOP_RIGHT:
		text.setOrigin(textBounds.left + textBounds.width, 0);
		break;
	case TextOrigin::TOP_CENTER:
		text.setOrigin(textBounds.width / 2.0f, 0);
		break;
	case TextOrigin::CENTER:
		text.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
		break;
	default:
		break;
	}
}