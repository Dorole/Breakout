#pragma once
#include <SFML/Graphics.hpp>

class Window
{
private:
	//int width;
	//int height;
	//sf::Vector2i position {};
	
public:
	sf::RenderWindow createRenderWindow(int width, int height, const char* name )
	{
		sf::RenderWindow window(sf::VideoMode(width, height), name);
		return window;
	}

};

