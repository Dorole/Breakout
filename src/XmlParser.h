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
	int getNodeAttributeAsInt(const char* attributeName, const Args&... args) 
	{
		return getAttributeIntValue(doc, attributeName, args...);
	}

	template <typename... Args>
	std::string getNodeAttributeAsString(const char* attributeName, const Args&... args)
	{
		return getAttributeStringValue(doc, attributeName, args...);
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
	xml_node getNode(xml_node parent, const T& arg, const Args&... args) 
	{
		xml_node node = parent.child(arg);
		return node ? getNode(node, args...) : node;
	}

	/// <summary>
	/// Base case for recursion. Retrieves the child node
	/// by its name directly from the parent.
	/// </summary>
	template <typename T>
	xml_node getNode(xml_node parent, const T& arg) 
	{
		return parent.child(arg);
	}

	/// <summary>
	/// Recursive template function for getting an int attribute value
	/// from nested nodes.
	/// </summary>
	template <typename T, typename... Args>
	int getAttributeIntValue(xml_node parent, const char* attributeName, const T& arg, const Args&... args) 
	{
		xml_node node = parent.child(arg);
		return node ? getAttributeIntValue(node, args..., attributeName) : -1;
	}

	/// <summary>
	/// Base case for recursion (single node with attribute) for retrieving 
	/// attribute value as int.
	/// </summary>
	template <typename T>
	int getAttributeIntValue(xml_node parent, const char* attributeName, const T& arg) 
	{
		xml_attribute attribute = parent.child(arg).attribute(attributeName);
		return attribute ? attribute.as_int() : -1;
	}

	/// <summary>
	/// Recursive template function for getting a string attribute value
	/// from nested nodes.
	/// </summary>
	template <typename T, typename... Args>
	std::string getAttributeStringValue(xml_node parent, const char* attributeName, const T& arg, const Args&... args)
	{
		xml_node node = parent.child(arg);
		return node ? getAttributeStringValue(node, args..., attributeName) : "No node found";
	}

	/// <summary>
	/// Base case for recursion (single node with attribute) for retrieving 
	/// attribute value (string).
	/// </summary>
	template <typename T>
	std::string getAttributeStringValue(xml_node parent, const char* attributeName, const T& arg)
	{
		xml_attribute attribute = parent.child(arg).attribute(attributeName);
		return attribute ? attribute.value() : "No value found";
	}
};

