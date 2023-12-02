#include <iostream>
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "TextCreator.h"
#include "UIManager.h"
#include "NumValueObserver.h"

using namespace sf;

UIManager::UIManager(RenderWindow& windowRef, ValueGetter& valueGetterRef)  //unsubscribe
	: window(windowRef), valueGetter(valueGetterRef)
{
	font.loadFromFile("resources/fonts/Cartoon Blocks Christmas.otf"); //get iz gameConfig-a

	textCreator = TextCreator(textOffsetTop, textOffsetSide);

	auto levelText = textCreator.createNewText(window, font, "level:", TextAlignment::TOP_LEFT, fontSize);
	auto scoreText = textCreator.createNewText(window, font, "score:", TextAlignment::TOP_RIGHT, fontSize);
	auto livesText = textCreator.createNewText(window, font, "lives:", TextAlignment::TOP_CENTER, fontSize); //TEMP

	Vector2f posBelowLevelText = levelText->getPosition() + Vector2f(0, levelText->getLocalBounds().height + verticalSpacing);
	Vector2f posBelowScoreText = scoreText->getPosition() + Vector2f(0, scoreText->getLocalBounds().height + verticalSpacing);
	Vector2f posBelowLivesText = livesText->getPosition() + Vector2f(0, scoreText->getLocalBounds().height + verticalSpacing); //TEMP

	levelValueText = textCreator.createNewText(font, std::to_string(valueGetter.getLevel()), posBelowLevelText, fontSize, TextOrigin::TOP_CENTER); //vjerojatno nece trebati valueGetter nego GameConfig ref
	scoreValueText = textCreator.createNewText(font, std::to_string(0), posBelowScoreText, fontSize, TextOrigin::TOP_CENTER);
	currentLivesText = textCreator.createNewText(font, "3", posBelowLivesText, fontSize, TextOrigin::TOP_CENTER); //TEMP - get from config

	labelTexts.push_back(std::move(levelText));
	labelTexts.push_back(std::move(scoreText));
	labelTexts.push_back(std::move(livesText)); //TEMP


	//fullHeartTex.loadFromFile("resources/textures/heart_full.png");
	//emptyHeartTex.loadFromFile("resources/textures/heart_empty.png");

	//fullHeartSprite.setTexture(fullHeartTex);
	//emptyHeartSprite.setTexture(emptyHeartTex);

	//fullHeartSprite.setScale(4, 4); //remove

	//fullHeartSprite.setOrigin(fullHeartSprite.getLocalBounds().width / 2, fullHeartSprite.getLocalBounds().height / 2);
	//emptyHeartSprite.setOrigin(emptyHeartSprite.getLocalBounds().width / 2, emptyHeartSprite.getLocalBounds().height / 2);

	//fullHeartSprite.setPosition(window.getSize().x / 2, 50); //fix

}


// ****************************** OVERRIDDEN FUNCTIONS ******************************


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
	window.draw(*currentLivesText); //TEMP

	//window.draw(fullHeartSprite);
}

//vjerojatno ce trebati enum ili nesto da se odredi koji valueChange se gleda
void UIManager::onValueChanged(int value, ValueType valueType)
{	
	switch (valueType)
	{
	case ValueType::SCORE:
		scoreValueText->setString(std::to_string(value));
		std::cout << "Score: " << value << std::endl;
		break;
	case ValueType::LIVES:
		currentLivesText->setString(std::to_string(value));
		std::cout << "Lives: " << value << std::endl;
		break;
	default:
		break;
	}
	
}