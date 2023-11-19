#include "XmlParser.h"
#include "pugixml.hpp"
#include <iostream> //remove

using namespace pugi;

bool XmlParser::loadDocument(const char* filePath)
{
	if (doc.load_file(filePath))
	{
		std::cout << "File loaded" << std::endl; //remove
		return true;
	}

	std::cout << "File NOT loaded" << std::endl; //remove
	return false;
}






