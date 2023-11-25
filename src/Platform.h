#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ValueGetter.h"

using namespace sf;

//odvojiti vizual od logike

class Platform : public GameObject
{
private: //move these to GameObject
    RenderWindow& window;
    Texture texture;
    Sprite sprite;
    Vector2f initialPlatformPosition;
    FloatRect spriteBounds;
    bool windowBoundReached = false;

    //move these to GameObject
    void setSpriteOriginToCenter();
    void getSpriteBounds();
    void setInitialPlatformPosition();
    void movePlatform();

public:
    Platform(RenderWindow& windowRef, ValueGetter& valueGetter);
    void update() override;
    void draw() override;

    Vector2f getInitialPlatformPosition() { return initialPlatformPosition; }
    Vector2f getPlatformPosition() { return sprite.getPosition(); }
    FloatRect getPlatformBounds() { return spriteBounds; }
    bool platformWindowBoundReached() { return windowBoundReached; } //MAKE EVENT!!
};

