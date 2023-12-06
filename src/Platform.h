#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ValueGetter.h"

using namespace sf;

class Platform : public GameObject
{
private:

    // ************************* PRIVATE STATE ************************
    Texture texture;
    Sprite sprite;
    Vector2f initialPlatformPosition;
    FloatRect spriteLocalBounds;

    float platformSpeed{ 400.0f }; 
    bool windowBoundReached = false;

    // ************************* PRIVATE FUNCTIONS ************************
    void setSpriteOriginToCenter();
    void getSpriteLocalBounds();
    void setInitialPlatformPosition();
    void movePlatform(float deltaTime);

    // ************************* PUBLIC FUNCTIONS ************************
public:
    Platform(RenderWindow& windowRef, ValueGetter& valueGetterRef);

    // inherited via GameObject
    void init() override;
    void update(float deltaTime) override;
    void draw() override;

    Vector2f getInitialPlatformPosition() { return initialPlatformPosition; }
    Vector2f getPlatformPosition() { return sprite.getPosition(); }
    FloatRect getPlatformLocalBounds() { return spriteLocalBounds; }
    FloatRect getPlatformGlobalBounds() { return sprite.getGlobalBounds(); }
    bool platformWindowBoundReached() { return windowBoundReached; } 

};

