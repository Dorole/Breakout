#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ValueGetter.h"
#include "LevelDataObserver.h"

using namespace sf;

//odvojiti vizual od logike

class Platform : public GameObject, public LevelDataObserver
{
private: //move these to GameObject
    RenderWindow& window;
    ValueGetter& valueGetter;

    Texture texture;
    Sprite sprite;
    Vector2f initialPlatformPosition;
    FloatRect spriteLocalBounds;

    float platformSpeed = 400.0f; //set from ctr!
    bool windowBoundReached = false;

    void init();

    //move these to GameObject
    void setSpriteOriginToCenter();
    void getSpriteLocalBounds();
    void setInitialPlatformPosition();
    void movePlatform(float deltaTime);

public:
    Platform(RenderWindow& windowRef, ValueGetter& valueGetterRef);
    void update(float deltaTime) override;
    void draw() override;

    Vector2f getInitialPlatformPosition() { return initialPlatformPosition; }
    Vector2f getPlatformPosition() { return sprite.getPosition(); }
    FloatRect getPlatformLocalBounds() { return spriteLocalBounds; }
    FloatRect getPlatformGlobalBounds() { return sprite.getGlobalBounds(); }
    bool platformWindowBoundReached() { return windowBoundReached; } 


    // Inherited via LevelDataObserver
    virtual void onLevelChanged() override;

};

