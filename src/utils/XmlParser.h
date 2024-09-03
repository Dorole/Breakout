#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <limits>
#include "pugi/pugixml.hpp"

using namespace pugi;

/// <summary>
/// Wrapper class for pugixml.
/// </summary>
class XmlParser
{
public:
	bool loadDocument(const char* filePath);
	bool isFileAlreadyLoaded(const std::string& filePath);

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
	std::string getNodeAttributeAsString(const std::string& attributeName, const Args&... args)
	{
		return getAttributeStringValue(doc, attributeName, args...);
	}

	/// <summary>
	/// Retrieves the string value of the specified child node's specified attribute.
	/// </summary>
	/// <param name="targetAttributeName">The attribute based on which children nodes are compared.</param>
	/// <param name="targetAttributeValue">The value of the attribute based on which the child node is selected.</param>
	/// <param name="attributeToRetrieve">The attribute whose value is desired.</param>
	template <typename... Args>
	std::string getSiblingNodeAttributeAsString(const std::string& targetAttributeName, const std::string& targetAttributeValue, const std::string& attributeToRetrieve, const Args&... args)
	{
		xml_node siblingNode = getChildNodeByAttributeValue(doc, targetAttributeName, targetAttributeValue, args...);

		if (siblingNode)
			return getAttributeStringValueByAttributeName(siblingNode, attributeToRetrieve);
		else
		{
			std::cout << "No sibling node found." << std::endl;
			return "No value found";
		}
	}

	/// <summary>
	/// Retrieves the int value of the specified child node's specified attribute.
	/// </summary>
	/// <param name="targetAttributeName">The attribute based on which children nodes are compared.</param>
	/// <param name="targetAttributeValue">The value of the attribute based on which the child node is selected.</param>
	/// <param name="attributeToRetrieve">The attribute whose value is desired.</param>
	template <typename... Args>
	int getSiblingNodeAttributeAsInt(const std::string& targetAttributeName, const std::string& targetAttributeValue, const std::string& attributeToRetrieve, const Args&... args)
	{
		xml_node siblingNode = getChildNodeByAttributeValue(doc, targetAttributeName, targetAttributeValue, args...);

		if (siblingNode)
			return getAttributeIntValueByAttributeName(siblingNode, attributeToRetrieve);
		else
		{
			std::cout << "No sibling node found." << std::endl;
			return -42;
		}
	}

	/// <summary>
	/// Retrieves a vector with string values of a specified attribute for sibling nodes.
	/// </summary>
	template <typename... Args>
	std::vector<std::string> getSiblingAttributesValuesByType(std::string attributeName, const Args&... args)
	{
		return getChildAttributeValuesByType(doc, attributeName, args...);
	}

	/// <summary>
	/// Checks whether the designated child node has the desired attribute.
	/// </summary>
	template <typename... Args>
	bool checkSiblingNodeAttributeExists(const std::string& targetAttributeName, const std::string& targetAttributeValue, const std::string& attributeToRetrieve, const Args&... args)
	{
		xml_node siblingNode = getChildNodeByAttributeValue(doc, targetAttributeName, targetAttributeValue, args...);

		return checkAttributeExists(siblingNode, attributeToRetrieve);
	}


private:
	xml_document doc;
	std::string currentFilePath = "";

	/// <summary>
	/// Retrieves the string value of a specified attribute in the specified node.
	/// </summary>
	std::string getAttributeStringValueByAttributeName(xml_node node, const std::string& attributeToRetrieve)
	{

		const char* attributeName = attributeToRetrieve.c_str();
		xml_attribute attribute = node.attribute(attributeName);
		return attribute.value();
	}

	/// <summary>
	/// Retrieves the int value of a specified attribute in the specified node.
	/// </summary>
	int getAttributeIntValueByAttributeName(xml_node node, const std::string& attributeToRetrieve)
	{
		const char* attributeName = attributeToRetrieve.c_str();
		xml_attribute attribute = node.attribute(attributeName);

		if (attribute)
		{
			if (std::isdigit(attribute.value()[0]) || (attribute.value()[0] == '-' && std::isdigit(attribute.value()[1])))
				return attribute.as_int();
			else
			{
				constexpr int result = std::numeric_limits<int>::max();
				std::cout << "Attribute value is not an int. Returning special value: " << result << std::endl;
				return result;
			}
		}
		else
		{
			std::cout << "Attribute " << attributeName << " not found." << std::endl;
			return std::numeric_limits<int>::max();
		}


	}

	bool checkAttributeExists(xml_node node, const std::string& attributeToCheck)
	{
		const char* attributeName = attributeToCheck.c_str();
		xml_attribute attribute = node.attribute(attributeName);

		if (attribute)
			return true;

		return false;
	}

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
	/// Without this, the getNode args don't get properly converted.
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
		return node ? getAttributeIntValue(node, args..., attributeName) : -42;
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
		return attribute ? attribute.as_int() : -42;
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
	/// Loops through children of a specified node and retrieves the 
	/// child node by a specified attribute value.
	/// </summary>
	/// <param name="parent">Root parent, the document.</param>
	/// <param name="attributeName_s">The attribute based on which children nodes are compared.</param>
	/// <param name="attributeValue_s">The value of the attribute based on which the child node is selected.</param>
	/// <returns>The child node whose specified attribute corresponds the specified value.</returns>
	template <typename... Args>
	xml_node getChildNodeByAttributeValue(xml_node parent, std::string attributeName_s, std::string attributeValue_s, const Args&... args)
	{
		xml_node node = getNode(parent, args...);

		if (!node)
		{
			std::cout << "No node found." << std::endl;
			return xml_node();
		}

		const char* attributeName = attributeName_s.c_str();
		const char* attributeValue = attributeValue_s.c_str();
		xml_node childNode = node.find_child_by_attribute(attributeName, attributeValue);
		if (!childNode)
		{
			std::cout << "No child node with provided attribute name or attribute value found." << std::endl;
			return xml_node();
		}

		return childNode;
	}

	/// <summary>
	/// Loops through children of the specified node and 
	/// stores values of the specified attribute of each child in a string vector.
	/// </summary>
	template <typename... Args>
	std::vector<std::string> getChildAttributeValuesByType(xml_node parent, std::string attributeName_s, const Args&... args)
	{
		std::vector<std::string> valueVector{};

		xml_node node = getNode(parent, args...);

		if (!node)
		{
			std::cout << "No node found." << std::endl;
			return valueVector;
		}

		const char* attributeName = attributeName_s.c_str();

		for (const auto& childNode : node.children())
		{
			const char* attributeValue = childNode.attribute(attributeName).value();
			std::string s(attributeValue);
			valueVector.push_back(s);
		}

		return valueVector;
	}

};



