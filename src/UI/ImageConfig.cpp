#include "ImageConfig.h"

using namespace sf;

void ImageConfig::setImageOriginCenter(Sprite& sprite)
{
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void ImageConfig::configureImage(RenderWindow& window, Texture& texture, Sprite& sprite)
{
	setImageOriginCenter(sprite);

	float windowX = static_cast<float>(window.getSize().x);
	float windowY = static_cast<float>(window.getSize().y);

	float scaleFactor = std::max(windowX / texture.getSize().x, windowY / texture.getSize().y);

	sprite.setScale(scaleFactor, scaleFactor);
	sprite.setPosition(windowX / 2, windowY / 2);
}
