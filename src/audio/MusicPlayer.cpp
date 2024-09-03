#include "MusicPlayer.h"

const std::string MusicPlayer::MAIN_MENU_MUSIC = "MainMenuMusic";
const std::string MusicPlayer::GAME_OVER_MUSIC = "GameOverMusic";
const std::string MusicPlayer::LEVEL_CLEAR_MUSIC = "LevelClearMusic";
const std::string MusicPlayer::GAME_FINISHED_MUSIC = "GameFinishedMusic";


MusicPlayer::MusicPlayer(ValueGetter& valueGetterRef)
	: valueGetter(valueGetterRef)
{
	valueGetter.attachLevelDataObserver(this);
	valueGetter.attachInitReadyObserver(this);
	music.setVolume(defaultMusicVolume);
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

void MusicPlayer::onInit()
{
	mainMenuMusicPath = valueGetter.getGeneralAsset(MAIN_MENU_MUSIC);
	gameOverMusicPath = valueGetter.getGeneralAsset(GAME_OVER_MUSIC);
	levelClearMusicPath = valueGetter.getGeneralAsset(LEVEL_CLEAR_MUSIC);
	gameFinishedMusicPath = valueGetter.getGeneralAsset(GAME_FINISHED_MUSIC);

	levelMusicPath = valueGetter.getLevelMusicPath();
}

void MusicPlayer::onInteract(InteractionType interactionType)
{
	isSoundOn = !isSoundOn;
	music.setVolume(isSoundOn ? defaultMusicVolume : 0.0f);
}

