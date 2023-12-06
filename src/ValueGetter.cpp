#include <filesystem>
#include <iostream>
#include <stdexcept>
#include "ValueGetter.h"
#include "XmlParser.h"
#include "BrickTypeValues.h"
#include "LevelLoader.h"

const std::string ValueGetter::LEVEL = "Level";
const std::string ValueGetter::ID = "Id";
const std::string ValueGetter::BRICKS = "Bricks";
const std::string ValueGetter::ROW_COUNT = "RowCount";
const std::string ValueGetter::COLUMN_COUNT = "ColumnCount";
const std::string ValueGetter::ROW_SPACING = "RowSpacing";
const std::string ValueGetter::COLUMN_SPACING = "ColumnSpacing";
const std::string ValueGetter::GRID_OFFSET = "GridOffsetTop";
const std::string ValueGetter::BACKGROUND_TEXTURE = "BackgroundTexture";
const std::string ValueGetter::PLATFORM_TEXTURE = "PlatformTexture";
const std::string ValueGetter::BALL_TEXTURE = "BallTexture";
const std::string ValueGetter::LEVEL_MUSIC = "LevelMusic";

const std::string ValueGetter::BRICK_TYPES = "BrickTypes";
const std::string ValueGetter::BRICK_TYPE = "BrickType";
const std::string ValueGetter::TEXTURE = "Texture";
const std::string ValueGetter::HIT_POINTS = "HitPoints";
const std::string ValueGetter::HIT_SOUND = "HitSound";
const std::string ValueGetter::BREAK_SOUND = "BreakSound";
const std::string ValueGetter::BREAK_SCORE = "BreakScore";

const std::string ValueGetter::DOC_PATH = "resources/xml files/";
const std::string ValueGetter::EXTENSION = ".xml";

int ValueGetter::rowCount = 0;
int ValueGetter::columnCount = 0;
int ValueGetter::columnSpacing = 0;
int ValueGetter::rowSpacing = 0;
int ValueGetter::gridOffset = 0;
int ValueGetter::levelId = 0;

std::string ValueGetter::bricksLayout = "";
std::string ValueGetter::backgroundTexturePath = "";
std::string ValueGetter::platformTexturePath = "";
std::string ValueGetter::ballTexturePath = "";
std::string ValueGetter::defaultFontPath = "resources/fonts/Cartoon Blocks Christmas.otf";
std::string ValueGetter::levelMusicPath = "";

std::vector<std::string> ValueGetter::bricksIds{};
std::map<std::string, BrickTypeValues> ValueGetter::brickTypesMap{};
std::vector<LevelDataObserver*> ValueGetter::levelDataObservers{};

std::string ValueGetter::getXmlFilePath(std::string& fileName) const
{
	std::filesystem::path fullPath = DOC_PATH;
	fullPath /= fileName;
	fullPath += EXTENSION;

	return fullPath.string();
}

//consts for brick IDs!!
ValueGetter::ValueGetter(XmlParser& parserRef, LevelLoader& levelLoaderRef)
	: parser(parserRef), levelLoader(levelLoaderRef)
{
	levelLoader.attachLevelObserver(this);
	getLevelValues(0);
}

BrickTypeValues ValueGetter::getBrickTypeValues(const std::string& brickId)
{
	BrickTypeValues currentBrick;
	currentBrick.id = brickId;
	currentBrick.texture = parser.getSiblingNodeAttributeAsString(ID, brickId, TEXTURE, LEVEL, BRICK_TYPES);
	currentBrick.hitPoints = parser.getSiblingNodeAttributeAsInt(ID, brickId, HIT_POINTS, LEVEL, BRICK_TYPES);
	currentBrick.hitSound = parser.getSiblingNodeAttributeAsString(ID, brickId, HIT_SOUND, LEVEL, BRICK_TYPES);
	
	if (parser.checkSiblingNodeAttributeExists(ID, brickId, BREAK_SOUND, LEVEL, BRICK_TYPES))
		currentBrick.breakSound = parser.getSiblingNodeAttributeAsString(ID, brickId, BREAK_SOUND, LEVEL, BRICK_TYPES);

	if (parser.checkSiblingNodeAttributeExists(ID, brickId, BREAK_SCORE, LEVEL, BRICK_TYPES))
		currentBrick.breakScore = parser.getSiblingNodeAttributeAsInt(ID, brickId, BREAK_SCORE, LEVEL, BRICK_TYPES);

	return currentBrick;
}

void ValueGetter::mapBrickValuesToIds()
{
	for (const auto& id : bricksIds)
	{
		brickTypesMap[id] = getBrickTypeValues(id);
	}
}

BrickTypeValues ValueGetter::getBrickValuesById(const std::string& brickId)
{
	if (brickTypesMap.find(brickId) != brickTypesMap.end())
		return brickTypesMap.at(brickId);
	else
		throw std::out_of_range("Key not found.");
}

void ValueGetter::getLevelValues(int levelIndex)
{
	std::string levelFileName = levelLoader.getFileName(levelIndex);
	parser.loadDocument(getXmlFilePath(levelFileName).c_str());

	rowCount = parser.getNodeAttributeAsInt(ROW_COUNT, LEVEL);
	columnCount = parser.getNodeAttributeAsInt(COLUMN_COUNT, LEVEL);
	rowSpacing = parser.getNodeAttributeAsInt(ROW_SPACING, LEVEL);
	columnSpacing = parser.getNodeAttributeAsInt(COLUMN_SPACING, LEVEL);
	gridOffset = parser.getNodeAttributeAsInt(GRID_OFFSET, LEVEL);
	levelId = parser.getNodeAttributeAsInt(ID, LEVEL);


	bricksLayout = parser.getTextFromNode(LEVEL, BRICKS);
	backgroundTexturePath = parser.getNodeAttributeAsString(BACKGROUND_TEXTURE, LEVEL);
	platformTexturePath = parser.getNodeAttributeAsString(PLATFORM_TEXTURE, LEVEL);
	ballTexturePath = parser.getNodeAttributeAsString(BALL_TEXTURE, LEVEL);
	levelMusicPath = parser.getNodeAttributeAsString(LEVEL_MUSIC, LEVEL);

	bricksIds = parser.getSiblingAttributesValuesByType(ID, LEVEL, BRICK_TYPES);

	mapBrickValuesToIds();
}

void ValueGetter::onValueChanged(int value, ValueType valueType)
{
	if (valueType == ValueType::LEVEL)
	{
		getLevelValues(value);

		for (const auto& observer : levelDataObservers)
			observer->onLevelChanged();
	}
}

void ValueGetter::attachLevelDataObserver(LevelDataObserver* observer)
{
	levelDataObservers.push_back(observer);
}