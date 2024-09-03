#pragma once

enum class SpritePosition
{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	TOP_CENTRE, //objects span top_left & top_right
	BOTTOM_CENTRE, //objects span bottom_left & bottom_right
	LEFT_CENTRE, // objects span top_left & bottom_left
	RIGHT_CENTRE, // objects span top_right & bottom_right
	CENTRE // object spans top_left, top_right, bottom_left & bottom_right
};

