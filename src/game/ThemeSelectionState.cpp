#include "ThemeSelectionState.h"

ThemeSelectionState::ThemeSelectionState(Game& game) 
	: GameState(game),
	summerButton(game.getSoundPlayer()),
	winterButton(game.getSoundPlayer()),
	loadingScreen(window)
{
	attachThemeSelectionObserver(&themeManager);
	attachThemeSelectionObserver(&valueGetter);
	selfInit();
}

void ThemeSelectionState::selfInit()
{
	winterFont.loadFromFile(valueGetter.previewTheme(Theme::WINTER, THEME_FONT));
	summerFont.loadFromFile(valueGetter.previewTheme(Theme::SUMMER, THEME_FONT));
	setButtonElements();
	setTextElements();
}


void ThemeSelectionState::handleInput(sf::Event& event)
{
	handleButtonInteraction(event, summerButton, Theme::SUMMER);
	handleButtonInteraction(event, winterButton, Theme::WINTER);
}

void ThemeSelectionState::draw()
{
	summerButton.drawButton(window);
	winterButton.drawButton(window);	
}

void ThemeSelectionState::onStateExit()
{
	themeSelectionObservers.clear();
	stateObservers.clear();
}

void ThemeSelectionState::setButtonElements()
{
	float buttonWidth = window.getSize().x * buttonWidthPercentage / 100.0f;
	float buttonHeight = window.getSize().y * buttonHeightPercentage / 100.0f;
	Vector2f buttonSize = Vector2f(buttonWidth, buttonHeight);

	float buttonTextSize = buttonHeight * buttonTextSizePercentage / 100.0f;

	float buttonSpacing = window.getSize().y * buttonSpacingPercentage / 100.0f;
	Vector2f summerButtonPosition = Vector2f(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - (2 * buttonSpacing));
	Vector2f winterButtonPosition = Vector2f(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) + (2 * buttonSpacing));

	summerButton.configureButton(SUMMER_TEXT, buttonSize, summerFont, buttonTextSize, summerButtonColor, summerButtonTextColor);
	winterButton.configureButton(WINTER_TEXT, buttonSize, winterFont, buttonTextSize, winterButtonColor, winterButtonTextColor);

	summerButton.setButtonOutline(1.0f, summerButtonTextColor);
	winterButton.setButtonOutline(1.0f, winterButtonTextColor);

	summerButton.setButtonPosition(summerButtonPosition, buttonTextOffset);
	winterButton.setButtonPosition(winterButtonPosition, buttonTextOffset);
}

void ThemeSelectionState::attachValueObserver(HUDObserver* observer)
{
}

void ThemeSelectionState::attachStateObserver(StateObserver* observer)
{
	stateObservers.push_back(observer);
}

void ThemeSelectionState::attachThemeSelectionObserver(ThemeSelectionObserver* observer)
{
	themeSelectionObservers.push_back(observer);
}

void ThemeSelectionState::handleButtonInteraction(sf::Event& event, Button& button, Theme theme)
{
	if (button.buttonInteract(window, event))
	{
		selectedTheme = theme;
		displayLoading();

		for (const auto& observer : themeSelectionObservers)
			observer->onThemeSelected(theme);

		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::MAIN_MENU);
	}
}

void ThemeSelectionState::displayLoading()
{
	Font font = selectedTheme == Theme::SUMMER ? summerFont : winterFont;
	Color textColor = selectedTheme == Theme::SUMMER ? summerTheme.titleColor : Color::White;
	loadingScreen.displayLoading(font, textColor);
}


void ThemeSelectionState::init() {}
void ThemeSelectionState::onStateEnter() {}
void ThemeSelectionState::update(float deltaTime) {}
void ThemeSelectionState::setTextElements() {}
