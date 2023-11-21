#include "Game.h"
#include <SFML/Graphics.hpp>
#include "XmlParser.h"
#include "GameObject.h"
#include "Platform.h"
#include "../BrickGrid.h"

using namespace sf;

Game::Game(RenderWindow& windowRef)
	: window(windowRef)
{
	//should be able to change path from constructor!
	parser.loadDocument("resources/xml files/Level_1.xml");

	std::string platformTexturePath = parser.getNodeAttributeAsString("PlatformTexture", "Level");

	//Create objects
	auto platform = std::make_unique<Platform>(window, platformTexturePath);
	gameObjects.push_back(std::move(platform)); //pazi ako planiras jos koristiti platform, sad je platform nullptr! --> push_back direktno

	BrickGrid grid(parser, "Level", "ColumnCount", "RowCount", "ColumnSpacing", "RowSpacing");
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