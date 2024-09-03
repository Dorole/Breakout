#pragma once
#include <SFML/Graphics.hpp>
#include "events/ThemeSelectionObserver.h"
#include <iostream>
struct ThemeData
{
	sf::Color buttonColor;
	sf::Color buttonTextColor;
	sf::Color textColor;
	sf::Color hudColor;
	sf::Color titleColor;
	sf::Color outlineColor;
	float outlineThickness{0};

	ThemeData(){}
	ThemeData(sf::Color button, sf::Color buttonText, sf::Color text, sf::Color hud, sf::Color title, sf::Color outline, float outlThickness)
		: buttonColor(button), 
		buttonTextColor(buttonText), 
		textColor(text), 
		hudColor(hud), 
		titleColor(title) ,
		outlineColor(outline),
		outlineThickness(outlThickness)
	{}
};


class ThemeManager : public ThemeSelectionObserver
{
private:
	const ThemeData summerThemeData
	{
		sf::Color(0, 205, 205),		//button - light blue
		sf::Color::Yellow,			//button text
		sf::Color::Yellow,			//text
		sf::Color(240, 158, 187),	//hud - pinkish
		sf::Color::Yellow,			//title
		sf::Color::Black,			//outline
		1.0f						//outline thickness
	};

	const ThemeData winterThemeData
	{
		sf::Color::White,		//button
		sf::Color(0, 0, 102),	//button text - deep blue
		sf::Color::White,		//text
		sf::Color(0, 0, 102),	//hud
		sf::Color(0, 0, 102),	//title
		sf::Color::Black,		//outline
		0.0f					//outlineThickness
	};

	ThemeData currentThemeData = summerThemeData;

	void setTheme(const ThemeData& theme);

public:

	const ThemeData& getCurrentTheme() const { return currentThemeData; }
	const ThemeData& getThemeData(Theme theme) const;

	// Inherited via ThemeSelectionObserver
	virtual void onThemeSelected(Theme theme) override;

};