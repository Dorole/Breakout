#include <iostream>
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "UIManager.h"
#include "Game.h"

using namespace sf;

UIManager::UIManager(RenderWindow& windowRef, ValueGetter& valueGetterRef, Game& gameRef) //mozda mu Grid ni ne treba?
	: window(windowRef), valueGetter(valueGetterRef), game(gameRef)
{
	font.loadFromFile("resources/fonts/Cartoon Blocks Christmas.otf"); //mozda isto iz xml-a? 

	auto levelText = createNewText(font, "level:", TextAlignment::TOP_LEFT, fontSize);
	auto scoreText = createNewText(font, "score:", TextAlignment::TOP_RIGHT, fontSize);

	Vector2f posBelowLevelText = levelText->getPosition() + Vector2f(0, levelText->getLocalBounds().height + verticalSpacing);
	Vector2f posBelowScoreText = scoreText->getPosition() + Vector2f(0, scoreText->getLocalBounds().height + verticalSpacing);

	levelValueText = createNewText(font, std::to_string(valueGetter.getLevel()), posBelowLevelText, fontSize, TextOrigin::TOP_CENTER);
	scoreValueText = createNewText(font, std::to_string(0), posBelowScoreText, fontSize, TextOrigin::TOP_CENTER);

	texts.push_back(std::move(levelText));
	texts.push_back(std::move(scoreText));


	fullHeartTex.loadFromFile("resources/textures/heart_full.png");
	emptyHeartTex.loadFromFile("resources/textures/heart_empty.png");

	fullHeartSprite.setTexture(fullHeartTex);
	emptyHeartSprite.setTexture(emptyHeartTex);

	fullHeartSprite.setOrigin(fullHeartSprite.getLocalBounds().width / 2, fullHeartSprite.getLocalBounds().height / 2);
	emptyHeartSprite.setOrigin(emptyHeartSprite.getLocalBounds().width / 2, emptyHeartSprite.getLocalBounds().height / 2);

	fullHeartSprite.setPosition(window.getSize().x / 2, 10);

	game.attachObserver(this);
}

std::unique_ptr<Text> UIManager::createNewText(Font& font, std::string textString, TextAlignment alignment, unsigned int charSize)
{
	auto text = std::make_unique<Text>();

	text->setFont(font);
	text->setString(textString);
	text->setCharacterSize(charSize);

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
			textPosition = Vector2f(window.getSize().x / 2, textOffsetTop);
			break;
		default:
			break;
	}


	text->setPosition(textPosition);

	return text;
}

std::unique_ptr<Text> UIManager::createNewText(Font& font, std::string textString, Vector2f position, unsigned int charSize, TextOrigin txtOrigin)
{
	auto text = std::make_unique<Text>();

	text->setFont(font);
	text->setString(textString);
	text->setCharacterSize(charSize);
	setTextOrigin(txtOrigin, *text);
	text->setPosition(position);

	return text;
}


void UIManager::setTextOrigin(TextOrigin origin, Text& text)
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
		text.setOrigin(textBounds.width / 2, 0);
		break;
	default:
		break;
	}
}


// ****************************** OVERRIDDEN FUNCTIONS ******************************

void UIManager::update()
{

}

void UIManager::draw()
{
	for (const auto& txt : texts)
	{
		window.draw(*txt);
	}

	window.draw(*levelValueText);
	window.draw(*scoreValueText);

	window.draw(fullHeartSprite);
}

void UIManager::onValueChanged(int value)
{	
	scoreValueText->setString(std::to_string(value));
}