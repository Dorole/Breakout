#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ValueGetter.h"

using namespace sf;

//odvojiti vizual od logike

class Platform : public GameObject
{
private:
    RenderWindow& window;
    Texture texture;
    Sprite sprite;
    Vector2f initialPlatformPosition;
    FloatRect spriteBounds;

    void setSpriteOriginToCenter();
    void getSpriteBounds();
    void setInitialPlatformPosition();
    void movePlatform();

public:
    Platform(RenderWindow& windowRef, ValueGetter& valueGetter);
    void update() override;
    void draw() override;
};

