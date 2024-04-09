#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "BrickTypeValues.h"
#include "ValueGetter.h"
#include "Collidable.h"
#include "CollisionObserver.h"
#include "CollisionManager.h"
#include "BrickObserver.h"

using namespace sf;

class Brick : public CollisionObserver
{
protected:

	FloatRect spriteBounds;
	Sprite sprite;
	std::string id;
	Texture texture;
	int hitPoints = 0;
	int breakScore = 0;

	Collidable collidable;
	SoundBuffer hitBuffer;
	SoundBuffer breakBuffer;
	Sound brickSound;

	//used to prevent multiple hits "at once"
	Clock cooldownTimer;
	float coolDownDuration = 0.5f;
	
	void createBrick(BrickTypeValues values);

	std::vector<BrickObserver*> brickObservers;
	void notifyBrickObservers();

public:

	Brick();
	Brick(ValueGetter& valueGetter);
	
	virtual void onHit() = 0;
	virtual void reloadBrickValues(ValueGetter& valueGetter) = 0;

	Sprite& getSprite() { return sprite; }
	FloatRect& getSpriteBounds() { return spriteBounds; }
	int getBreakScore() const;
	std::string getBrickId() { return id; }
	
	void setSpritePosition(Vector2f position) { sprite.setPosition(position); }
	FloatRect getSpriteGlobalBounds() { return sprite.getGlobalBounds(); }

	bool shouldDestroy() { return hitPoints == 0; }

	Collidable& getCollidable() { return collidable; }

	// Inherited via CollisionObserver
	virtual void onCollision(Collidable& collidedObject) override;
	void observeCollision(CollisionManager& collisionManager);

	void attachBrickObserver(BrickObserver* observer);
};

