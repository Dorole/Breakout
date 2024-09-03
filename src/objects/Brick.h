#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "BrickTypeValues.h"
#include "audio/SoundPlayer.h"
#include "utils/ValueGetter.h"
#include "collision/Collidable.h"
#include "collision/CollisionManager.h"
#include "events/CollisionObserver.h"
#include "events/BrickObserver.h"
#include "events/BrickSoundObserver.h"

using namespace sf;

class Brick : public CollisionObserver
{
protected:

	FloatRect spriteBounds;
	Sprite sprite;
	std::string brickTypeId;
	Texture texture;
	int hitPoints = 0;
	int breakScore = 0;

	Collidable collidable;
	int collidableId;

	std::string hitSoundPath = "";
	std::string breakSoundPath = "";

	//used to prevent multiple hits "at once"
	Clock cooldownTimer;
	float coolDownDuration = 0.5f;

	void createBrick(BrickTypeValues values);

	std::vector<BrickObserver*> brickObservers;
	std::vector<BrickSoundObserver*> brickSoundObservers;

	void notifyBrickObservers();
	void attachBrickSoundObserver(BrickSoundObserver* observer);
	void notifyBrickSoundObservers(std::string& brickId, SoundType soundType);

public:

	Brick();
	Brick(ValueGetter& valueGetter, SoundPlayer& soundPlayer);

	virtual void onHit() = 0;
	void reloadBrickValues(ValueGetter& valueGetter, SoundPlayer& soundPlayer);

	Sprite& getSprite() { return sprite; }
	FloatRect& getSpriteBounds() { return spriteBounds; }
	int getBreakScore() const;
	std::string getBrickId() { return brickTypeId; }

	void setSpritePosition(Vector2f position) { sprite.setPosition(position); }
	FloatRect getSpriteGlobalBounds() { return sprite.getGlobalBounds(); }

	bool shouldDestroy() { return hitPoints == 0; }

	Collidable& getCollidable() { return collidable; }

	// Inherited via CollisionObserver
	virtual void onCollision(Collidable& collidedObject) override;
	void observeCollision(CollisionManager& collisionManager);

	void attachBrickObserver(BrickObserver* observer);
};



