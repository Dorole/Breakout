#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ValueGetter.h"
//#include "PlayerController.h"

using namespace sf;

class Platform : public GameObject//, public PlayerController
{
private:

    // ************************* PRIVATE STATE ************************
    Texture texture;
    Sprite sprite;
    Vector2f initialPlatformPosition{};
    FloatRect spriteLocalBounds;

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


    // Inherited via PlayerController
    //Vector2f getInitialPosition() const override;
    //Vector2f getPosition() const override;
    //bool getWindowBoundReached() const override;
    //FloatRect getLocalBounds() const override;
    //FloatRect getGlobalBounds() const override;

};

