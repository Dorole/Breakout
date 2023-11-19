#pragma once

#include "pugixml.hpp"

using namespace pugi;

/// <summary>
/// Wrapper class for pugixml.
/// </summary>
class XmlParser
{
public:
	bool loadDocument(const char* filePath);

	//get texture - or just get texture path (as string)?
	//get sound - or as above?

	/// <summary>
	/// Gets text from an XML node. If the node is nested, 
	/// list all higher level nodes as arguments, in order from higher to lower.
	/// </summary>
	/// <typeparam name="...Args">Args variadic template parameter for node names.</typeparam>
	/// <param name="...args">Nodes listed from higher level to lower.</param>
	/// <returns>Text content of the node.</returns>
	template <typename... Args>
	std::string getTextFromNode(const Args&... args) 
	{
		xml_node node = getNode(doc, args...);

		if (!node.text().empty()) 
			return node.text().get();
		else 
			return "No text content found!";

	}

	/// <summary>
	/// Gets a value of an XML node attribute as int.
	/// </summary>
	/// <param name="attributeName"></param>
	/// <param name="...args">Nodes listed from higher level to lower.</param>
	template <typename... Args>
	int getNodeAttributeAsInt(const char* attributeName, const Args&... args) {
		return getAttributeValue(doc, attributeName, args...);
	}
	

private:
	xml_document doc;

	/// <summary>
	/// Recursive template function for navigating 
	/// through nested XML nodes. It starts with a parent node, 
	/// retrieves the first child node by its name, then 
	/// calls itself recursively until the base node is reached. 
	/// </summary>
	template <typename T, typename... Args>
	xml_node getNode(xml_node parent, const T& arg, const Args&... args) {
		xml_node node = parent.child(arg);
		return node ? getNode(node, args...) : node;
	}

	/// <summary>
	/// Base case for recursion. Retrieves the child node
	/// by its name directly from the parent.
	/// </summary>
	template <typename T>
	xml_node getNode(xml_node parent, const T& arg) {
		return parent.child(arg);
	}

	// Recursive helper function to navigate through nested nodes with attributes
	template <typename T, typename... Args>
	int getAttributeValue(xml_node parent, const char* attributeName, const T& arg, const Args&... args) {
		xml_node node = parent.child(arg);
		return node ? getAttributeValue(node, args..., attributeName) : -1;
	}

	// Base case for recursion (single node with attribute)
	template <typename T>
	int getAttributeValue(xml_node parent, const char* attributeName, const T& arg) {
		xml_attribute attribute = parent.child(arg).attribute(attributeName);
		return attribute ? attribute.as_int() : -1;
	}
};

