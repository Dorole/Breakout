#include "BrickMedium.h"
#include <iostream>

BrickMedium::BrickMedium(ValueGetter& valueGetter, SoundPlayer& soundPlayer) : Brick(valueGetter, soundPlayer)
{
	createBrick(valueGetter.getBrickValuesById("M"));
	attachBrickSoundObserver(&soundPlayer);
	soundPlayer.registerBrickSound(brickTypeId, hitSoundPath, breakSoundPath);
}

void BrickMedium::onHit()
{
	float elapsedTime = cooldownTimer.getElapsedTime().asSeconds();
	if ((elapsedTime <= coolDownDuration) || hitPoints <= 0) return;

	hitPoints--;

	if (hitPoints == 0)
	{
		notifyBrickSoundObservers(brickTypeId, SoundType::BRICK_BREAK);
		notifyBrickObservers();
	}
	else
		notifyBrickSoundObservers(brickTypeId, SoundType::BRICK_HIT);

	cooldownTimer.restart();
};
