#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "BrickTypeValues.h"
#include "ValueGetter.h"


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

	SoundBuffer hitBuffer;
	SoundBuffer breakBuffer;
	Sound brickSound;
	
	void createBrick(BrickTypeValues values);

public:

	Brick();
	Brick(ValueGetter& valueGetter);
	
	/// <summary>
	/// Deduct hitPoints.
	/// Send event if hitPoints are 0 --> change state of renderVector in BrickGrid
	/// </summary>
	virtual void onHit() = 0;
	virtual void reloadBrickValues(ValueGetter& valueGetter) = 0;

	Sprite& getSprite() { return sprite; }
	FloatRect& getSpriteBounds() { return spriteBounds; }
	int getBreakScore() const;
	std::string getBrickId() { return id; }
	
	void setSpritePosition(Vector2f position) { sprite.setPosition(position); }
	FloatRect getSpriteGlobalBounds() { return sprite.getGlobalBounds(); }

	bool shouldDestroy() { return hitPoints == 0; }

	
};

