#include "Game.h"
#include <SFML/Graphics.hpp>
#include "XmlParser.h"
#include "GameObject.h"
#include "Platform.h"

using namespace sf;

Game::Game(RenderWindow& windowRef)
	: window(windowRef)
{
	//should be able to change path from constructor!
	parser.loadDocument("resources/xml files/Level_1.xml");

	std::string platformTexturePath = parser.getNodeAttributeAsString("PlatformTexture", "Level");

	//Create objects
	gameObjects.push_back(std::make_unique<Platform>(Vector2f(window.getSize().x / 2, window.getSize().y - 20), window, platformTexturePath));
}

void Game::update()
{
	for (auto& gameObject : gameObjects)
	{
		gameObject->update();
	}
}

void Game::render()
{
	for (auto& gameObject : gameObjects)
	{
		gameObject->draw(window);
	}

	window.display();
	window.clear();
}