#pragma once

enum class SpritePosition
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	TOP_CENTRE, //special - objects span top_left & top_right
	BOTTOM_CENTRE, //special - objects span bottom_left & bottom_right
	LEFT_CENTRE, //special - objects span top_left & bottom_left
	RIGHT_CENTRE, //special - objects span top_right & bottom_right
	CENTRE, //special - object spans top_left, top_right, bottom_left & bottom_right
};
