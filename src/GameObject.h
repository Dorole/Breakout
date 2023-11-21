#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject
{
protected:
	Sprite sprite;
	FloatRect spriteBounds;
	Texture texture;

	void setSpriteOriginToCenter();
	void getSpriteBounds();

public:
	virtual void update() = 0;
	void draw(RenderWindow& window);

};

