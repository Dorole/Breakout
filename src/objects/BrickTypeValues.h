#pragma once
#include <string>

struct BrickTypeValues
{
	std::string id {};
	std::string texture{};
	int hitPoints{};
	std::string hitSound{};
	int breakScore{};
	std::string breakSound{};
};

