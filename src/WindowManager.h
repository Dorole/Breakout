#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class WindowManager
{
private:
	RenderWindow window;

public:
	WindowManager(int width, int height, const char* title)
		: window(VideoMode(width, height), title)
	{

	}

	RenderWindow& getWindow() { return window; }
	
	void run();
};

