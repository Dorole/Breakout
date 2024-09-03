#pragma once
#include <filesystem>
#include <map>
#include <vector>
#include "objects/BrickTypeValues.h"
#include "utils/XmlParser.h"
#include "game/LevelLoader.h"
#include "events/HUDObserver.h"
#include "events/LevelDataObserver.h"
#include "events/ThemeSelectionObserver.h"
#include "events/InitReadyObserver.h"
#include <iostream>

class ValueGetter : public HUDObserver, public ThemeSelectionObserver
{
private:
	XmlParser parser;
	LevelLoader& levelLoader;

	//********************************* STATIC MEMBERS *********************************
	//************************* REFERENCES TO NODES & ATTRIBUTES ************************

	static const std::string THEME;
	static const std::string LEVEL;
	static const std::string ID;
	static const std::string BRICKS;
	static const std::string ROW_COUNT;
	static const std::string COLUMN_COUNT;
	static const std::string ROW_SPACING;
	static const std::string COLUMN_SPACING;
	static const std::string GRID_OFFSET;
	static const std::string BACKGROUND_TEXTURE;
	static const std::string PLATFORM_TEXTURE;
	static const std::string BALL_TEXTURE;
	static const std::string LEVEL_MUSIC;

	static const std::string BRICK_TYPES;
	static const std::string BRICK_TYPE;
	static const std::string TEXTURE;
	static const std::string HIT_POINTS;
	static const std::string HIT_SOUND;
	static const std::string BREAK_SOUND;
	static const std::string BREAK_SCORE;

	static const std::filesystem::path BASE_ASSETS_PATH;
	static const std::filesystem::path XML_FILES_DIR;
	static const std::string EXTENSION;
	static const std::string GENERAL_FILE;

	//********************************* STATE *********************************
	static int rowCount;
	static int columnCount;
	static int columnSpacing;
	static int rowSpacing;
	static int gridOffset;
	static int levelId;

	static std::string generalAssetsPath;
	static std::string s_theme;
	static std::string bricksLayout;
	static std::string platformTexturePath;
	static std::string backgroundTexturePath;
	static std::string ballTexturePath;
	static std::string levelMusicPath;

	static std::vector<std::string> bricksIds;
	static std::map<std::string, BrickTypeValues> brickTypesMap;
	static std::vector<LevelDataObserver*> levelDataObservers;
	static std::vector<InitReadyObserver*> initReadyObservers;

	//********************************* PRIVATE FUNCTIONS *********************************

	std::string getXmlFilePath(std::string& fileName) const;
	BrickTypeValues getBrickTypeValues(const std::string& brickId);
	void mapBrickValuesToIds();
	void getLevelValues(int levelIndex);
	void setTheme(Theme selectedTheme);
	void setGeneralAssetsFile();

	//********************************* PUBLIC FUNCTIONS *********************************
public:
	ValueGetter(LevelLoader& levelLoaderRef);

	static int getRowCount() { return rowCount; }
	static int getColumnCount() { return columnCount; }
	static int getRowSpacing() { return rowSpacing; }
	static int getColumnSpacing() { return columnSpacing; }
	static int getGridOffset() { return gridOffset; }
	static int getLevel() { return levelId; }
	static std::string getBricksLayout() { return bricksLayout; }
	static std::string getPlatformTexturePath() { return platformTexturePath; }
	static std::string getBackgroundTexturePath() { return backgroundTexturePath; }
	static std::string getBallTexturePath() { return ballTexturePath; }
	static std::string getLevelMusicPath() { return levelMusicPath; }
	static std::vector<std::string> getBricksIds() { return bricksIds; }

	std::string previewTheme(Theme previewTheme, const std::string& nodeName);
	std::string getGeneralAsset(const std::string& nodeName);
	
	BrickTypeValues getBrickValuesById(const std::string& brickId);

	// Inherited via HUDObserver
	void onValueChanged(int value, ValueType valueType) override;

	void attachLevelDataObserver(LevelDataObserver* observer);
	void attachInitReadyObserver(InitReadyObserver* observer);

	// Inherited via ThemeSelectionObserver
	virtual void onThemeSelected(Theme theme) override;
};





