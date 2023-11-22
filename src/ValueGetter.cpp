#include <filesystem>
#include "ValueGetter.h"
#include "XmlParser.h"

const std::string ValueGetter::LEVEL = "Level";
const std::string ValueGetter::BRICKS = "Bricks";
const std::string ValueGetter::ROW_COUNT = "RowCount";
const std::string ValueGetter::COLUMN_COUNT = "ColumnCount";
const std::string ValueGetter::ROW_SPACING = "RowSpacing";
const std::string ValueGetter::COLUMN_SPACING = "ColumnSpacing";
const std::string ValueGetter::BACKGROUND_TEXTURE = "BackgroundTexture";
const std::string ValueGetter::PLATFORM_TEXTURE = "PlatformTexture";

const std::string ValueGetter::DOC_PATH = "resources/xml files/";
const std::string ValueGetter::EXTENSION = ".xml";

int ValueGetter::rowCount = 0;
int ValueGetter::columnCount = 0;
int ValueGetter::columnSpacing = 0;
int ValueGetter::rowSpacing = 0;

std::string ValueGetter::bricksLayout = "";
std::string ValueGetter::backgroundTexture = "";
std::string ValueGetter::platformTexture = "";

std::string ValueGetter::getXmlFilePath(std::string& fileName) const
{
	std::filesystem::path fullPath = DOC_PATH;
	fullPath /= fileName;
	fullPath += EXTENSION;

	return fullPath.string();
}

ValueGetter::ValueGetter(XmlParser& parserRef, std::string& levelFileName)
	: parser{ parserRef }
{
	parser.loadDocument(getXmlFilePath(levelFileName).c_str());

	rowCount = parser.getNodeAttributeAsInt(ROW_COUNT, LEVEL);
	columnCount = parser.getNodeAttributeAsInt(COLUMN_COUNT, LEVEL);
	rowSpacing = parser.getNodeAttributeAsInt(ROW_SPACING, LEVEL);
	columnSpacing = parser.getNodeAttributeAsInt(COLUMN_SPACING, LEVEL);

	bricksLayout = parser.getTextFromNode(LEVEL, BRICKS);
	backgroundTexture = parser.getNodeAttributeAsString(BACKGROUND_TEXTURE, LEVEL);
	platformTexture = parser.getNodeAttributeAsString(PLATFORM_TEXTURE, LEVEL);
}
