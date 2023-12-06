#include "AudioPlayer.h"

void AudioPlayer::onLevelChanged()
{
	levelMusicPath = valueGetter.getLevelMusicPath();
}
