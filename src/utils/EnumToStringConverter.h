#pragma once
#include <iostream>
#include "collision/SpritePosition.h"
#include "collision/CollidableObjectType.h"
#include "UI/Theme.h"

/// <summary>
/// Helper class used for debugging purposes.
/// </summary>
struct EnumToStringConverter
{
	std::string spritePositionToString(SpritePosition positionEnum)
	{
		switch (positionEnum)
		{
		case SpritePosition::TOP_LEFT:
			return "TOP LEFT";
		case SpritePosition::TOP_RIGHT:
			return "TOP RIGHT";
		case SpritePosition::BOTTOM_LEFT:
			return "BOTTOM LEFT";
		case SpritePosition::BOTTOM_RIGHT:
			return "BOTTOM RIGHT";
		case SpritePosition::TOP_CENTRE:
			return "TOP CENTRE";
		case SpritePosition::BOTTOM_CENTRE:
			return "BOTTOM CENTRE";
		case SpritePosition::LEFT_CENTRE:
			return "LEFT CENTRE";
		case SpritePosition::RIGHT_CENTRE:
			return "RIGHT CENTRE";
		case SpritePosition::CENTRE:
			return "CENTRE";
		default:
			return "";
		}
	}

	std::string collidableTypeToString(CollidableObjectType typeEnum)
	{
		switch (typeEnum)
		{
		case CollidableObjectType::BALL:
			return "BALL";
		case CollidableObjectType::PLATFORM:
			return "PLATFORM";
		case CollidableObjectType::BRICK:
			return "BRICK";
		default:
			return "";
		}
	}

	std::string themeToString(Theme theme)
	{
		switch (theme)
		{
		case Theme::WINTER:
			return "winter";
		case Theme::SUMMER:
			return "summer";
		default:
			return "";
		}
	}
};
