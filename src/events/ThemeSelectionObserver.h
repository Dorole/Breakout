#pragma once
#include "UI/Theme.h"

class ThemeSelectionObserver
{
public:
	virtual void onThemeSelected(Theme theme) = 0;
};
