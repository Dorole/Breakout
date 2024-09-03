#include "BrickImpenetrable.h"
#include <iostream>


BrickImpenetrable::BrickImpenetrable(ValueGetter& valueGetter, SoundPlayer& soundPlayer)
	: Brick(valueGetter, soundPlayer)
{
	createBrick(valueGetter.getBrickValuesById("I"));
	attachBrickSoundObserver(&soundPlayer);
	soundPlayer.registerBrickSound(brickTypeId, hitSoundPath, breakSoundPath);
}

void BrickImpenetrable::onHit()
{
	notifyBrickSoundObservers(brickTypeId, SoundType::BRICK_HIT);
	return;
};