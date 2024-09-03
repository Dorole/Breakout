#include "BrickSoft.h"
#include <SFML/Audio.hpp>

BrickSoft::BrickSoft(ValueGetter& valueGetter, SoundPlayer& soundPlayer) : Brick(valueGetter, soundPlayer)
{
	createBrick(valueGetter.getBrickValuesById("S"));
	attachBrickSoundObserver(&soundPlayer);
	soundPlayer.registerBrickSound(brickTypeId, hitSoundPath, breakSoundPath);
}

void BrickSoft::onHit()
{
	if (hitPoints <= 0) return;

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


