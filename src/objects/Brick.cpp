#include "Brick.h"

Brick::Brick()
	: collidable(sprite, CollidableObjectType::BRICK)
{
	collidableId = collidable.getId();
}

Brick::Brick(ValueGetter& valueGetter, SoundPlayer& soundPlayer)
	: collidable(sprite, CollidableObjectType::BRICK)
{
	collidableId = collidable.getId();
}

void Brick::createBrick(BrickTypeValues values)
{
	brickTypeId = values.id;
	hitPoints = values.hitPoints;
	breakScore = values.breakScore;

	texture.loadFromFile(values.texture);
	sprite.setTexture(texture);
	spriteBounds = sprite.getLocalBounds();

	hitSoundPath = values.hitSound;
	breakSoundPath = values.breakSound;
}

void Brick::reloadBrickValues(ValueGetter& valueGetter, SoundPlayer& soundPlayer)
{
	createBrick(valueGetter.getBrickValuesById(brickTypeId));
	soundPlayer.reloadBrickSound(brickTypeId, hitSoundPath, breakSoundPath);
}

int Brick::getBreakScore() const
{
	return breakScore;
}

void Brick::onCollision(Collidable& collidedObject)
{
	if (collidedObject.getCollidableObjectType() == CollidableObjectType::BRICK &&
		collidedObject.getId() == collidableId)
	{
		onHit();

		if (shouldDestroy())
			collidedObject.setActiveStatus(false);
	}
}

void Brick::observeCollision(CollisionManager& collisionManager)
{
	collisionManager.attachCollisionObserver(this);
}

void Brick::attachBrickObserver(BrickObserver* observer)
{
	brickObservers.push_back(observer);
}

void Brick::attachBrickSoundObserver(BrickSoundObserver* observer)
{
	brickSoundObservers.push_back(observer);
}

void Brick::notifyBrickObservers()
{
	for (const auto& brickObserver : brickObservers)
		brickObserver->onBrickDestroyed(*this);
}

void Brick::notifyBrickSoundObservers(std::string& brickId, SoundType soundType)
{
	for (const auto& brickSoundObserver : brickSoundObservers)
		brickSoundObserver->onBrickPlaySound(brickId, soundType);
}
