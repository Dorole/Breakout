#include "UIManager.h"

using namespace sf;

const std::string UIManager::PAUSE_SCREEN = "PauseScreen";
const std::string UIManager::FONT_PATH = "ThemeFont";
const std::string UIManager::PAUSED_TEXT = "PAUSED";
const std::string UIManager::RESUME_TEXT = "RESUME";
const std::string UIManager::MENU_TEXT = "MENU";

UIManager::UIManager(RenderWindow& windowRef, Game& game)
	: window(windowRef), 
	valueGetter(game.getValueGetter()),
	resumeButton(game.getSoundPlayer()),
	menuButton(game.getSoundPlayer())
{
	valueGetter.attachLevelDataObserver(this);
	currentTheme = &game.getThemeManager().getCurrentTheme();
	setTextElements();
	setButtonElements();
	setBackgroundImage();
}

void UIManager::handleInput(sf::Event& event)
{
	if (!paused) return;

	if (resumeButton.buttonInteract(window, event))
	{
		togglePause();
		for (const auto& observer : interactionObservers)
			observer->onInteract(InteractionType::RESUME);
	}

	if (menuButton.buttonInteract(window, event))
	{
		togglePause();
		for (const auto& observer : interactionObservers)
			observer->onInteract(InteractionType::MENU);
	}
}

void UIManager::update() {}

void UIManager::draw()
{
	for (const auto& txt : labelTexts)
	{
		window.draw(*txt);
	}

	window.draw(*levelValueText);
	window.draw(*scoreValueText);
	window.draw(*currentLivesText);

	if (paused)
	{
		window.draw(pauseBackground);
		window.draw(*pausedText);
		for (Button& button : buttons)
			button.drawButton(window);
	}
}

void UIManager::setTextElements()
{
	font.loadFromFile(valueGetter.getGeneralAsset(FONT_PATH));
	setHUDTextElements();
	setPauseTextElements();
}

void UIManager::setHUDTextElements()
{
	Color hudColor = currentTheme->hudColor;
	Color outlineColor = currentTheme->outlineColor;
	float outlineThickness = currentTheme->outlineThickness;

	float fontSize = window.getSize().y * fontSizePercentage / 100.0f;
	float textOffsetTop = window.getSize().y * textOffsetTopPercentage / 100.0f;
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
		txt->setFillColor(hudColor);
		txt->setOutlineThickness(outlineThickness);
		txt->setOutlineColor(outlineColor);
	}

	std::vector<std::reference_wrapper<Text>> valueTexts
	{
		std::ref(*levelValueText),
		std::ref(*scoreValueText),
		std::ref(*currentLivesText)
	};

	for (const auto& txt : valueTexts)
	{
		txt.get().setFillColor(hudColor);
		txt.get().setOutlineThickness(outlineThickness);
		txt.get().setOutlineColor(outlineColor);
	}
}

void UIManager::setPauseTextElements()
{
	Color pausedTextColor = currentTheme->titleColor;

	float pauseTextSize = window.getSize().y * pauseTextSizePercentage / 100.0f;
	float topOffset = window.getSize().y * pauseTextTopOffsetPercentage / 100.0f;

	TextCreator textCreator(topOffset, 0);
	pausedText = textCreator.createNewText(window, font, PAUSED_TEXT, TextAlignment::TOP_CENTER, pauseTextSize);
	pausedText->setFillColor(pausedTextColor);
}

void UIManager::setButtonElements()
{
	Color buttonColor = currentTheme->buttonColor;
	Color buttonTextColor = currentTheme->buttonTextColor;

	float buttonWidth = window.getSize().x * buttonWidthPercentage / 100.0f;
	float buttonHeight = window.getSize().y * buttonHeightPercentage / 100.0f;
	Vector2f buttonSize = Vector2f(buttonWidth, buttonHeight);

	float buttonTextSize = buttonHeight * buttonTextSizePercentage / 100.0f;

	float buttonSpacing = window.getSize().y * buttonSpacingPercentage / 100.0f;
	Vector2f startButtonPosition = Vector2f(window.getSize().x / 2.0f, (window.getSize().y / 2.0f));
	Vector2f quitButtonPosition = Vector2f(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) + buttonSize.y + buttonSpacing);

	resumeButton.setButtonText(RESUME_TEXT);
	menuButton.setButtonText(MENU_TEXT);

	resumeButton.setButtonPosition(startButtonPosition, buttonTextOffset);
	menuButton.setButtonPosition(quitButtonPosition, buttonTextOffset);

	for (Button& button : buttons)
	{
		button.configureButton(buttonSize, font, buttonTextSize, buttonColor, buttonTextColor);
		button.setButtonOutline(1.0f, buttonTextColor);
	}
}

void UIManager::togglePause()
{
	paused = !paused;
	for (Button& button : buttons)
		button.setVisibility(paused);
}

void UIManager::setBackgroundImage()
{
	bgTexture.loadFromFile(valueGetter.getGeneralAsset(PAUSE_SCREEN));
	pauseBackground.setTexture(bgTexture);
	imageConfig.configureImage(window, bgTexture, pauseBackground);
}

void UIManager::attachInteractionObserver(InteractionObserver* observer)
{
	interactionObservers.push_back(observer);
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