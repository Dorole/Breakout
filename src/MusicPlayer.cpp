#include "MusicPlayer.h"

#include <SFML/Audio.hpp>
#include "ValueGetter.h"

MusicPlayer::MusicPlayer(ValueGetter& valueGetterRef)
	: valueGetter(valueGetterRef)
{
	valueGetter.attachLevelDataObserver(this);
	levelMusicPath = valueGetter.getLevelMusicPath();
	//music.setVolume(defaultMusicVolume);
	music.setVolume(0.0f);
}

void MusicPlayer::stopMusic()
{
	music.stop();
}

void MusicPlayer::loadPlayMusic(AudioType audioType)
{
	switch (audioType)
	{
	case AudioType::MAIN_MENU_MUSIC:
		music.setLoop(true);
		music.openFromFile(mainMenuMusicPath);
		break;
	case AudioType::LEVEL_MUSIC:
		music.setLoop(true);
		music.openFromFile(levelMusicPath);
		break;
	case AudioType::GAME_OVER_MUSIC:
		music.setLoop(false);
		music.openFromFile(gameOverMusicPath);
		break;
	case AudioType::LEVEL_CLEAR_MUSIC:
		music.setLoop(false);
		music.openFromFile(levelClearMusicPath);
		break;
	case AudioType::GAME_FINISHED_MUSIC:
		music.setLoop(false);
		music.openFromFile(gameFinishedMusicPath);
		break;
	default:
		break;
	}

	music.play();

}

void MusicPlayer::onLevelChanged()
{
	levelMusicPath = valueGetter.getLevelMusicPath();
}

