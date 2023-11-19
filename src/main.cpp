#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "pugixml.hpp"
#include <cctype>
#include <vector>

#include "XmlParser.h"


void SetShapeOriginToCenter(sf::Shape &shape)
{
	sf::FloatRect bounds = shape.getLocalBounds();
	shape.setOrigin(bounds.width / 2, bounds.height / 2);
}

void GameCode()
{
	// WINDOW
	sf::RenderWindow window(sf::VideoMode(1060, 1000), "Breakout"); //adjust
	window.setPosition({ 650, 150 });

	//SHAPE - PLATFORM
	sf::RectangleShape shape(sf::Vector2f(100, 10));
	SetShapeOriginToCenter(shape);
	shape.setPosition(window.getSize().x / 2, window.getSize().y - 20);
	shape.setFillColor(sf::Color::Cyan);
	sf::Vector2f initialShapePosition = shape.getPosition();

	//SHAPE - TEST BRICKS
	sf::RectangleShape brick_soft(sf::Vector2f(50, 20));
	brick_soft.setFillColor(sf::Color::White);

	sf::RectangleShape brick_medium(sf::Vector2f(50, 20));
	brick_medium.setFillColor(sf::Color::Magenta);

	sf::RectangleShape brick_hard(sf::Vector2f(50, 20));
	brick_hard.setFillColor(sf::Color::Blue);

	sf::RectangleShape brick_impenetrable(sf::Vector2f(50, 20));
	brick_impenetrable.setFillColor(sf::Color::Red);

	sf::RectangleShape no_brick(sf::Vector2f(50, 20));
	no_brick.setFillColor(sf::Color::Transparent);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Vector2i localMousePosition = sf::Mouse::getPosition(window);

		if (localMousePosition.x < 50) {
			shape.setPosition(50, initialShapePosition.y);
		}
		else if (localMousePosition.x > window.getSize().x - 50) {
			shape.setPosition(window.getSize().x - 50, initialShapePosition.y);
		}
		else {
			shape.setPosition(localMousePosition.x, initialShapePosition.y);
		}


		//for (size_t i = 0; i < columnCount; i++)
		//{
		//	for (size_t j = 0; j < rowCount; j++)
		//	{
		//		sf::RectangleShape l_brick;
		//		switch (charVector.at(j).at(i))
		//		{
		//		case 'S':
		//			l_brick = brick_soft;
		//			break;
		//		case 'M':
		//			l_brick = brick_medium;
		//			break;
		//		case 'H':
		//			l_brick = brick_hard;
		//			break;
		//		case 'I':
		//			l_brick = brick_impenetrable;
		//			break;
		//		case '_':
		//			l_brick = no_brick;
		//			break;
		//		default:
		//			break;
		//		}


		//		l_brick.setPosition(i * (l_brick.getSize().x + columnSpacing), j * (l_brick.getSize().y + rowSpacing)); //start needs to be adjusted
		//		window.draw(l_brick);
		//	}
		//}

		window.draw(shape);

		window.display();
		window.clear();
	}
}

void XML()
{
	//XML 
//pugi::xml_document doc;//
//pugi::xml_parse_result result = doc.load_file("resources/xml files/exampleLevel.xml");//

//pugi::xml_node levelNode = doc.child("Level");//
//
//int columnCount = levelNode.attribute("ColumnCount").as_int();//
//int rowCount = levelNode.attribute("RowCount").as_int();//
//int columnSpacing = levelNode.attribute("ColumnSpacing").as_int();//
//int rowSpacing = levelNode.attribute("RowSpacing").as_int();//
//
//pugi::xml_node bricksNode = doc.child("Level").child("Bricks");
//std::string bricksLayout = bricksNode.text().get();
//bricksLayout.erase(std::remove_if(bricksLayout.begin(), bricksLayout.end(), ::isspace), bricksLayout.end());
//
//std::vector<std::vector<char>> charVector;

//int index = 0;
//for (size_t i = 0; i < rowCount; i++)
//{
//	charVector.push_back(std::vector<char>());

//	for (size_t j = 0; j < columnCount; j++)
//	{
//		charVector.at(i).push_back(bricksLayout.at(index));
//		index++;
//	}
//}

//for (const auto& row : charVector) {
//	for (char brick : row) {
//		std::cout << brick << ' ';
//	}
//	std::cout << std::endl;
//}

// ************************************************************


	XmlParser parser;
	parser.loadDocument("resources/xml files/exampleLevel.xml");

	std::string bricksLayout = parser.getTextFromNode("Level", "Bricks");
	bricksLayout.erase(std::remove_if(bricksLayout.begin(), bricksLayout.end(), ::isspace), bricksLayout.end());

	std::cout << "Layout: " << bricksLayout << std::endl;
}

int main()
{
	XmlParser parser;
	parser.loadDocument("resources/xml files/exampleLevel.xml");

	int columnCount = parser.getNodeAttributeAsInt("ColumnCount", "Level");
	std::cout << "Column count: " << columnCount << std::endl;

	std::string bricksLayout = parser.getTextFromNode("Level", "Bricks");
	bricksLayout.erase(std::remove_if(bricksLayout.begin(), bricksLayout.end(), ::isspace), bricksLayout.end());

	std::cout << "Layout: " << bricksLayout << std::endl;

}