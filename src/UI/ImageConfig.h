#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class ImageConfig
{
private:

public:

	void setImageOriginCenter(Sprite& sprite);
	void configureImage(RenderWindow& window, Texture& texture, Sprite& sprite);

};
