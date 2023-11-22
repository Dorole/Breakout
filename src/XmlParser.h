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
		std::string nodeText = getNodeText(doc, args...);

		if (!nodeText.empty()) 
			return nodeText;
		else 
			return "No text content found!";

	}

	/// <summary>
	/// Gets a value of an XML node attribute as int.
	/// </summary>
	/// <param name="attributeName"></param>
	/// <param name="...args">Nodes listed from higher level to lower.</param>
	template <typename... Args>
	int getNodeAttributeAsInt(std::string attributeName, const Args&... args)
	{
		return getAttributeIntValue(doc, attributeName, args...);
	}

	template <typename... Args>
	std::string getNodeAttributeAsString(std::string attributeName, const Args&... args)
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
		xml_node node = getNodeImpl(parent, arg);
		return node ? getNode(node, args...) : node;
	}

	/// <summary>
	/// Base case for recursion. Retrieves the child node
	/// by its name directly from the parent.
	/// </summary>
	template <typename T>
	xml_node getNode(xml_node parent, const T& arg)
	{
		return getNodeImpl(parent, arg);
	}

	/// <summary>
	/// Specialization for std::string.
	/// Without this, the getNode ars don't get properly converted.
	/// </summary>
	xml_node getNodeImpl(xml_node parent, const std::string& arg)
	{
		return parent.child(arg.c_str());
	}

	/// <summary>
	/// Recursive template function for getting an int attribute value
	/// from nested nodes.
	/// </summary>
	template <typename T, typename... Args>
	int getAttributeIntValue(xml_node parent, std::string attributeName, const T& arg, const Args&... args)
	{
		xml_node node = parent.child(arg);
		return node ? getAttributeIntValue(node, args..., attributeName) : -1;
	}

	/// <summary>
	/// Base case for recursion (single node with attribute) for retrieving 
	/// attribute value as int.
	/// </summary>
	template <typename T>
	int getAttributeIntValue(xml_node parent, std::string attributeName_s, const T& arg) 
	{
		const char* attributeName = attributeName_s.c_str();
		xml_attribute attribute = parent.child(arg.c_str()).attribute(attributeName);
		return attribute ? attribute.as_int() : -1;
	}

	/// <summary>
	/// Recursive template function for getting a string attribute value
	/// from nested nodes.
	/// </summary>
	template <typename T, typename... Args>
	std::string getAttributeStringValue(xml_node parent, std::string attributeName, const T& arg, const Args&... args)
	{
		xml_node node = parent.child(arg);
		return node ? getAttributeStringValue(node, args..., attributeName) : "No node found";
	}

	/// <summary>
	/// Base case for recursion (single node with attribute) for retrieving 
	/// attribute value (string).
	/// </summary>
	template <typename T>
	std::string getAttributeStringValue(xml_node parent, std::string attributeName_s, const T& arg)
	{
		const char* attributeName = attributeName_s.c_str();
		xml_attribute attribute = parent.child(arg.c_str()).attribute(attributeName);
		return attribute ? attribute.value() : "No value found";
	}

	/// <summary>
	/// Recursive template function for getting a text content
	/// from a nested node.
	/// </summary>
	template <typename... Args>
	std::string getNodeText(xml_node parent, const Args&... args)
	{
		xml_node node = getNode(parent, args...);
		return node ? node.text().get() : "";
	}

	/// <summary>
	/// Base case for recursion for getting the text content
	/// of a single node.
	/// </summary>
	template <typename T>
	std::string getNodeText(xml_node parent, const T& arg)
	{
		xml_node node = parent.child(arg);
		return node ? node.text().get() : "";
	}





};

