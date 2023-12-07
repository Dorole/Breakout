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


class MusicPlayer : public LevelDataObserver
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
	MusicPlayer(ValueGetter& valueGetterRef);
	
	void stopMusic();
	void loadPlayMusic(AudioType audioType);

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;
};
