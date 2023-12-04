#pragma once
#include <map>
#include <vector>
#include "BrickTypeValues.h"
#include "XmlParser.h"
#include "GameConfig.h"
#include "NumValueObserver.h"
#include "LevelDataObserver.h"

class ValueGetter : public NumValueObserver
{
private:
	XmlParser& parser;
	GameConfig& gameConfig;

	//********************************* STATIC MEMBERS *********************************
	//************************* REFERENCES TO NODES & ATTRIBUTES ************************

	static const std::string LEVEL;
	static const std::string ID;
	static const std::string BRICKS;
	static const std::string ROW_COUNT;
	static const std::string COLUMN_COUNT;
	static const std::string ROW_SPACING;
	static const std::string COLUMN_SPACING;
	static const std::string BACKGROUND_TEXTURE;
	static const std::string PLATFORM_TEXTURE;
	static const std::string BALL_TEXTURE;

	static const std::string BRICK_TYPES;
	static const std::string BRICK_TYPE;
	static const std::string TEXTURE;
	static const std::string HIT_POINTS;
	static const std::string HIT_SOUND;
	static const std::string BREAK_SOUND;
	static const std::string BREAK_SCORE;

	static const std::string DOC_PATH;
	static const std::string EXTENSION;

	//********************************* STATE *********************************

	static int rowCount;
	static int columnCount;
	static int columnSpacing;
	static int rowSpacing;
	static int levelId;

	static std::string bricksLayout;
	static std::string platformTexturePath;
	static std::string backgroundTexturePath;
	static std::string ballTexturePath;

	static std::vector<std::string> bricksIds;
	static std::map<std::string, BrickTypeValues> brickTypesMap;
	static std::vector<LevelDataObserver*> levelDataObservers;

	//********************************* PRIVATE FUNCTIONS *********************************

	std::string getXmlFilePath(std::string& fileName) const;
	BrickTypeValues getBrickTypeValues(const std::string& brickId);
	void mapBrickValuesToIds();
	void getLevelValues(int levelIndex);

	//********************************* PUBLIC FUNCTIONS *********************************
public:
	ValueGetter(XmlParser& parserRef, GameConfig& gameConfigRef);

	//should probably make all these const!
	static int getRowCount() { return rowCount; }
	static int getColumnCount() { return columnCount; }
	static int getRowSpacing() { return rowSpacing; }
	static int getColumnSpacing() { return columnSpacing; }
	static int getLevel() { return levelId; }
	static std::string getBricksLayout() { return bricksLayout; }
	static std::string getPlatformTexturePath() { return platformTexturePath; }
	static std::string getBackgroundTexturePath() { return backgroundTexturePath; }
	static std::string getBallTexturePath() { return ballTexturePath; }
	static std::vector<std::string> getBricksIds() { return bricksIds; }

	BrickTypeValues getBrickValuesById(const std::string& brickId);

	// Inherited via NumValueObserver
	void onValueChanged(int value, ValueType valueType) override;

	void attachLevelDataObserver(LevelDataObserver* observer);
};



