#include "GameObjectRenderer.h"

GameObjectRenderer::GameObjectRenderer(Game& gameRef)
    : game(gameRef), window(gameRef.getWindow())
{}

void GameObjectRenderer::setSpriteOriginToCenter()
{
    sf::FloatRect spriteLocalBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteLocalBounds.width / 2, spriteLocalBounds.height / 2);
}

void GameObjectRenderer::init(std::string fileName, sf::Vector2f spriteScale)
{
    texture.loadFromFile(fileName);
    sprite.setTexture(texture);
    sprite.setScale(spriteScale);
    setSpriteOriginToCenter();
}

void GameObjectRenderer::setSpritePosition(const sf::Vector2f& position)
{
    sprite.setPosition(position);
}

void GameObjectRenderer::moveSprite(const sf::Vector2f& offset)
{
    sprite.move(offset);
}

void GameObjectRenderer::drawSprite()
{
    window.draw(sprite);
}