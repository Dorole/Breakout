#include "XmlParser.h"
#include "pugi/pugixml.hpp"
#include <iostream>

using namespace pugi;

bool XmlParser::loadDocument(const char* filePath)
{
	std::string s(filePath);

	if (doc.load_file(filePath))
	{
		//std::cout << "File loaded: " + s << std::endl;
		currentFilePath = s;
		return true;
	}

	std::cout << "File NOT loaded:" + s << std::endl; 
	return false;
}

bool XmlParser::isFileAlreadyLoaded(const std::string& filePath)
{
	return currentFilePath == filePath;
}
