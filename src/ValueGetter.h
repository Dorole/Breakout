#pragma once
#include "XmlParser.h"

class ValueGetter
{
private:
	XmlParser& parser;

	static const std::string LEVEL;
	static const std::string BRICKS;
	static const std::string ROW_COUNT;
	static const std::string COLUMN_COUNT;
	static const std::string ROW_SPACING;
	static const std::string COLUMN_SPACING;
	static const std::string BACKGROUND_TEXTURE;
	static const std::string PLATFORM_TEXTURE;

	static const std::string DOC_PATH;
	static const std::string EXTENSION;

	static int rowCount;
	static int columnCount;
	static int columnSpacing;
	static int rowSpacing;

	static std::string bricksLayout;
	static std::string platformTexture;
	static std::string backgroundTexture;


	std::string getXmlFilePath(std::string& fileName) const;

public:
	ValueGetter(XmlParser& parserRef, std::string& levelFileName);

	static int getRowCount() { return rowCount; }
	static int getColumnCount() { return columnCount; }
	static int getRowSpacing() { return rowSpacing; }
	static int getColumnSpacing() { return columnSpacing; }
	static std::string getBricksLayout() { return bricksLayout; }
	static std::string getPlatformTexture() { return platformTexture; }
	static std::string getBackgroundTexture() { return backgroundTexture; }
};

