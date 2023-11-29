#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "BrickTypeValues.h"
#include "ValueGetter.h"
#include "ISubject.h"

using namespace sf;

class Brick //: public ISubject
{
protected:

	FloatRect spriteBounds;
	Sprite sprite;
	std::string id;
	Texture texture;
	int hitPoints = 0;
	int breakScore = 0;
	//audio

	//std::vector<IObserver*> observers;

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
	FloatRect getSpriteGlobalBounds() { return sprite.getGlobalBounds(); }

	bool shouldDestroy() { return hitPoints == 0; }

	/*void Attach(IObserver* observer) override
	{
		observers.push_back(observer);
	}

	void Detach(IObserver* observer) override
	{
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}

	void Notify() override 
	{
		for (const auto& observer : observers)
			observer->onNotify();
	}*/
};

