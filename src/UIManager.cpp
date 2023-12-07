#include <iostream>
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "TextCreator.h"
#include "UIManager.h"
#include "NumValueObserver.h"

using namespace sf;

UIManager::UIManager(RenderWindow& windowRef, ValueGetter& valueGetterRef)  
	: window(windowRef), valueGetter(valueGetterRef)
{
	valueGetter.attachLevelDataObserver(this);
	setTextElements();
}

void UIManager::handleInput()
{
}

void UIManager::update()
{
}

void UIManager::draw()
{
	for (const auto& txt : labelTexts)
	{
		window.draw(*txt);
	}

	window.draw(*levelValueText);
	window.draw(*scoreValueText);
	window.draw(*currentLivesText); 
}

void UIManager::setTextElements()
{
	font.loadFromFile(valueGetter.getDefaultFontPath());

	float fontSize = window.getSize().y * fontSizePercentage/ 100.0f;
	float textOffsetTop = window.getSize().y  * textOffsetTopPercentage / 100.0f;
	float textOffsetSide = window.getSize().x * textOffsetSidePercentage / 100.0f;

	textCreator = TextCreator(textOffsetTop, textOffsetSide);

	auto levelText = textCreator.createNewText(window, font, "level:", TextAlignment::TOP_LEFT, fontSize);
	auto scoreText = textCreator.createNewText(window, font, "score:", TextAlignment::TOP_RIGHT, fontSize);
	auto livesText = textCreator.createNewText(window, font, "lives:", TextAlignment::TOP_CENTER, fontSize);

	Vector2f posBelowLevelText = levelText->getPosition() + Vector2f(0, levelText->getLocalBounds().height + verticalSpacing);
	Vector2f posBelowLivesText = livesText->getPosition() + Vector2f(0, livesText->getLocalBounds().height + verticalSpacing);
	adjustedScorePosition = Vector2f(scoreText->getPosition().x, scoreText->getPosition().y + scoreText->getLocalBounds().height + verticalSpacing);

	levelValueText = textCreator.createNewText(font, std::to_string(valueGetter.getLevel()), posBelowLevelText, fontSize, TextOrigin::TOP_CENTER);
	scoreValueText = textCreator.createNewText(font, std::to_string(0), adjustedScorePosition, fontSize, TextOrigin::TOP_CENTER);
	currentLivesText = textCreator.createNewText(font, "3", posBelowLivesText, fontSize, TextOrigin::TOP_CENTER);

	labelTexts.push_back(std::move(levelText));
	labelTexts.push_back(std::move(scoreText));
	labelTexts.push_back(std::move(livesText));

	for (const auto& txt : labelTexts)
	{
		txt->setFillColor(textColor);
	}

	levelValueText->setFillColor(textColor);
	scoreValueText->setFillColor(textColor);
	currentLivesText->setFillColor(textColor);
}

void UIManager::onValueChanged(int value, ValueType valueType)
{	
	switch (valueType)
	{
	case ValueType::SCORE:
		scoreValueText->setString(std::to_string(value));
		textCreator.setTextOrigin(TextOrigin::TOP_CENTER, *scoreValueText);
		scoreValueText->setPosition(adjustedScorePosition);
		break;
	case ValueType::LIVES:
		currentLivesText->setString(std::to_string(value));
		break;
	default:
		break;
	}
	
}

void UIManager::onLevelChanged()
{
	levelValueText->setString(std::to_string(valueGetter.getLevel()));
}
