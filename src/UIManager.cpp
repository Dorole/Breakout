#include <iostream>
#include <SFML/Graphics.hpp>
#include "ValueGetter.h"
#include "UIManager.h"
#include "Game.h"
#include "NumValueObserver.h"

using namespace sf;

UIManager::UIManager(RenderWindow& windowRef, ValueGetter& valueGetterRef, Game& gameRef)  //unsubscribe
	: window(windowRef), valueGetter(valueGetterRef), game(gameRef)
{
	font.loadFromFile("resources/fonts/Cartoon Blocks Christmas.otf"); //get iz gameConfig-a

	auto levelText = createNewText(font, "level:", TextAlignment::TOP_LEFT, fontSize);
	auto scoreText = createNewText(font, "score:", TextAlignment::TOP_RIGHT, fontSize);
	auto livesText = createNewText(font, "lives:", TextAlignment::TOP_CENTER, fontSize); //TEMP

	Vector2f posBelowLevelText = levelText->getPosition() + Vector2f(0, levelText->getLocalBounds().height + verticalSpacing);
	Vector2f posBelowScoreText = scoreText->getPosition() + Vector2f(0, scoreText->getLocalBounds().height + verticalSpacing);
	Vector2f posBelowLivesText = livesText->getPosition() + Vector2f(0, scoreText->getLocalBounds().height + verticalSpacing); //TEMP

	levelValueText = createNewText(font, std::to_string(valueGetter.getLevel()), posBelowLevelText, fontSize, TextOrigin::TOP_CENTER);
	scoreValueText = createNewText(font, std::to_string(0), posBelowScoreText, fontSize, TextOrigin::TOP_CENTER);
	currentLivesText = createNewText(font, "3", posBelowLivesText, fontSize, TextOrigin::TOP_CENTER); //TEMP - get from config

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