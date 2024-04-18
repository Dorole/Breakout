#include <SFML/Audio.hpp>
#include "Brick.h"
#include "ValueGetter.h"

Brick::Brick() 
	: collidable(sprite, CollidableObjectType::BRICK) 
{
	collidableId = collidable.getId();
}

Brick::Brick(ValueGetter& valueGetter) 
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
	
	hitBuffer.loadFromFile(values.hitSound);

	if (!values.breakSound.empty())
		breakBuffer.loadFromFile(values.breakSound);

	brickSound.setBuffer(hitBuffer);
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

void Brick::detachBrickObservers()
{
	brickObservers.clear();
}

void Brick::notifyBrickObservers()
{
	for (const auto& brickObserver : brickObservers)
		brickObserver->onBrickDestroyed(*this);
}
