#include "ThemeManager.h"
#include<iostream>

void ThemeManager::setTheme(const ThemeData& themeData)
{
	currentThemeData = themeData;
}

const ThemeData& ThemeManager::getThemeData(Theme theme) const
{
	switch (theme)
	{
	case Theme::WINTER:
		return winterThemeData;
	case Theme::SUMMER:
		return summerThemeData;
	default:
		return ThemeData();
	}
}

void ThemeManager::onThemeSelected(Theme theme)
{
	switch (theme)
	{
	case Theme::WINTER:
		setTheme(winterThemeData);
		break;
	case Theme::SUMMER:
		setTheme(summerThemeData);
		break;
	default:
		break;
	}
}
