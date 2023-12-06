#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <random>
#include <map>
#include "ValueGetter.h"
#include "LevelDataObserver.h"

enum class AudioType
{
	MAIN_MENU_MUSIC,
	LEVEL_MUSIC,
	GAME_OVER_MUSIC,
	LEVEL_CLEAR_MUSIC,
	GAME_FINISHED_MUSIC
};

using namespace sf;


class AudioPlayer : public LevelDataObserver
{
private:
	ValueGetter& valueGetter;
	Music music;

	float defaultMusicVolume = 70.0f;
	//static?
	const std::string mainMenuMusicPath = "resources/audio/MenuMusic.wav";
	const std::string gameOverMusicPath = "resources/audio/game_over_music.wav";
	const std::string levelClearMusicPath = "resources/audio/level_clear.wav";
	const std::string gameFinishedMusicPath = "resources/audio/game_clear.wav";
	std::string levelMusicPath = "";

public:
	AudioPlayer(ValueGetter& valueGetterRef)
		: valueGetter(valueGetterRef)
	{
		valueGetter.attachLevelDataObserver(this);
		levelMusicPath = valueGetter.getLevelMusicPath();
		music.setVolume(defaultMusicVolume);
	}
	
	void stopMusic()
	{
		music.stop();
	}

	void loadPlayMusic(AudioType audioType)
	{
		switch (audioType)
		{
		case AudioType::MAIN_MENU_MUSIC:
			music.openFromFile(mainMenuMusicPath);
			break;
		case AudioType::LEVEL_MUSIC:
			music.openFromFile(levelMusicPath);
			break;
		case AudioType::GAME_OVER_MUSIC:
			music.openFromFile(gameOverMusicPath);
			break;
		case AudioType::LEVEL_CLEAR_MUSIC:
			music.openFromFile(levelClearMusicPath);
			break;
		case AudioType::GAME_FINISHED_MUSIC:
			music.openFromFile(gameFinishedMusicPath);
			break;
		default:
			break;
		}

		music.play();

	}

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;
};
