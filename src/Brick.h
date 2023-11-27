#pragma once
#include <SFML/Graphics.hpp>
#include "BrickTypeValues.h"
#include "ValueGetter.h"
#include "Observer.h"

using namespace sf;

class Brick 
{
protected:

	FloatRect spriteBounds;
	Sprite sprite;
	std::string id;
	Texture texture;
	int hitPoints = 0;
	int breakScore = 0;
	//audio

	void createBrick(BrickTypeValues values);

public:

	Brick();
	Brick(ValueGetter& valueGetter);
	
	/// <summary>
	/// Deduct hitPoints.
	/// Send event if hitPoints are 0 --> change state of renderVector in BrickGrid
	/// </summary>
	virtual void onHit() = 0;

	Sprite& getSprite() { return sprite; }
	FloatRect& getSpriteBounds() { return spriteBounds; }
	void setSpritePosition(Vector2f position) { sprite.setPosition(position); }

};

