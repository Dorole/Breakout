#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Collidable.h"
#include "Game.h"
#include "ValueGetter.h"
#include "CollidableObjectType.h"

using namespace sf;

class Platform : public GameObject
{
private:

    // ************************* PRIVATE STATE ************************
    //CollisionManager& collisionManager;

    Texture texture;
    Sprite sprite;
    Vector2f initialPlatformPosition{};
    FloatRect spriteLocalBounds;

    Collidable collidable;

    float platformBottomOffset = 40.0f;
    float platformSpeed{ 400.0f }; 
    bool windowBoundReached = false;

    // ************************* PRIVATE FUNCTIONS ************************
    void setSpriteOriginToCenter();
    void getSpriteLocalBounds();
    void setInitialPlatformPosition();
    void movePlatform(float deltaTime);

    // ************************* PUBLIC FUNCTIONS ************************
public:
    Platform(Game& game);

    // inherited via GameObject
    void init() override;
    void update(float deltaTime) override;
    void draw() override;
    void registerForCollision() override;

    Vector2f getInitialPlatformPosition() { return initialPlatformPosition; }
    Vector2f getPlatformPosition() { return sprite.getPosition(); }
    FloatRect getPlatformLocalBounds() { return spriteLocalBounds; }
    FloatRect getPlatformGlobalBounds() { return sprite.getGlobalBounds(); }
    bool platformWindowBoundReached() { return windowBoundReached; } 
};

