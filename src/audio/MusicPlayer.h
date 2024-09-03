#pragma once
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "utils/ValueGetter.h"
#include "events/LevelDataObserver.h"
#include "events/InitReadyObserver.h"
#include "events/InteractionObserver.h"

enum class AudioType
{
	MAIN_MENU_MUSIC,
	LEVEL_MUSIC,
	GAME_OVER_MUSIC,
	LEVEL_CLEAR_MUSIC,
	GAME_FINISHED_MUSIC
};

using namespace sf;

class MusicPlayer : public LevelDataObserver, public InitReadyObserver, public InteractionObserver
{
private:
	ValueGetter& valueGetter;
	Music music;

	bool isSoundOn = true;
	float defaultMusicVolume = 60.0f;

	static const std::string MAIN_MENU_MUSIC;
	static const std::string GAME_OVER_MUSIC;
	static const std::string LEVEL_CLEAR_MUSIC;
	static const std::string GAME_FINISHED_MUSIC;

	std::string mainMenuMusicPath = "";
	std::string gameOverMusicPath = "";
	std::string levelClearMusicPath = "";
	std::string gameFinishedMusicPath = "";
	std::string levelMusicPath = "";

public:
	MusicPlayer(ValueGetter& valueGetterRef);

	void stopMusic();
	void loadPlayMusic(AudioType audioType);

	// Inherited via LevelDataObserver
	virtual void onLevelChanged() override;

	// Inherited via InitReadyObserver
	virtual void onInit() override;

	// Inherited via InteractionObserver
	virtual void onInteract(InteractionType interactionType) override;
};


