#include <iostream>
#include <stdexcept>
#include "ValueGetter.h"
#include "EnumToStringConverter.h"

const std::string ValueGetter::THEME = "Theme";
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

const std::filesystem::path ValueGetter::BASE_ASSETS_PATH = "assets";
const std::filesystem::path ValueGetter::XML_FILES_DIR = "xml_files";
const std::string ValueGetter::EXTENSION = ".xml";
const std::string ValueGetter::GENERAL_FILE = "General";

int ValueGetter::rowCount = 0;
int ValueGetter::columnCount = 0;
int ValueGetter::columnSpacing = 0;
int ValueGetter::rowSpacing = 0;
int ValueGetter::gridOffset = 0;
int ValueGetter::levelId = 0;

std::string ValueGetter::generalAssetsPath = "";
std::string ValueGetter::bricksLayout = "";
std::string ValueGetter::backgroundTexturePath = "";
std::string ValueGetter::platformTexturePath = "";
std::string ValueGetter::ballTexturePath = "";
std::string ValueGetter::levelMusicPath = "";

std::vector<std::string> ValueGetter::bricksIds{};
std::map<std::string, BrickTypeValues> ValueGetter::brickTypesMap{};
std::vector<LevelDataObserver*> ValueGetter::levelDataObservers{};
std::vector<InitReadyObserver*> ValueGetter::initReadyObservers{};

std::string ValueGetter::s_theme = "";


std::string ValueGetter::getXmlFilePath(std::string& fileName) const
{
	std::filesystem::path fullPath = BASE_ASSETS_PATH / s_theme / XML_FILES_DIR / fileName;
	fullPath += EXTENSION;

	return fullPath.string();
}

ValueGetter::ValueGetter(LevelLoader& levelLoaderRef)
	: parser(), levelLoader(levelLoaderRef)
{
	levelLoader.attachLevelObserver(this);
}

void ValueGetter::setGeneralAssetsFile()
{
	std::string general_file = GENERAL_FILE;
	generalAssetsPath = getXmlFilePath(general_file);	
}

std::string ValueGetter::getGeneralAsset(const std::string& nodeName)
{
	if (!parser.isFileAlreadyLoaded(generalAssetsPath))
		parser.loadDocument(generalAssetsPath.c_str());

	return parser.getNodeAttributeAsString(nodeName, THEME);
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
		throw std::out_of_range("Key not found in Brick Types Map.");
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

void ValueGetter::attachInitReadyObserver(InitReadyObserver* observer)
{
	initReadyObservers.push_back(observer);
}

void ValueGetter::setTheme(Theme selectedTheme)
{
	EnumToStringConverter converter;
	s_theme = converter.themeToString(selectedTheme);
}

void ValueGetter::onThemeSelected(Theme selectedTheme)
{
	setTheme(selectedTheme);
	setGeneralAssetsFile();
	getLevelValues(0);

	for (const auto& observer : initReadyObservers)
		observer->onInit();
}

std::string ValueGetter::previewTheme(Theme previewTheme, const std::string& nodeName)
{
	std::string currentTheme = s_theme;
	setTheme(previewTheme); 
	setGeneralAssetsFile();
	std::string assetPath = getGeneralAsset(nodeName);
	s_theme = currentTheme;
	return assetPath;
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
