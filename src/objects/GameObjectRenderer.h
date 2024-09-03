#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "game/Game.h"

class GameObjectRenderer
{
private:
    Game& game;
    sf::RenderWindow& window;

    sf::Texture texture;
    sf::Sprite sprite;

    void setSpriteOriginToCenter();

public:
    GameObjectRenderer(Game& gameRef);

    void init(std::string fileName, sf::Vector2f spriteScale = sf::Vector2f(1, 1));

    void setSpritePosition(const sf::Vector2f& position);
    void moveSprite(const sf::Vector2f& offset);
    void drawSprite();

    sf::Sprite& getSprite() { return sprite; }
    const sf::Vector2f& getSpritePosition() const { return sprite.getPosition(); }
    const sf::FloatRect getSpriteGlobalBounds() { return sprite.getGlobalBounds(); }
    const sf::FloatRect getSpriteLocalBounds() { return sprite.getLocalBounds(); }
};

