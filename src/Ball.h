#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ValueGetter.h"
#include "Platform.h"

class Ball : public GameObject
{
private: //move these to GameObject
    RenderWindow& window;
    Texture texture;
    Sprite sprite;
    Vector2f initialBallPosition;
    FloatRect spriteBounds;

    Platform& platform;

    //move these to GameObject
    void setSpriteOriginToCenter();
    void getSpriteBounds();
    void setInitialBallPosition();

    /// <summary>
    /// Moves the ball relative to the mouse position 
    /// and relative to the platform position before the game starts.
    /// </summary>
    void moveIdle();


public:
    Ball(RenderWindow& windowRef, ValueGetter& valueGetter, Platform& platformRef);

    void update() override;
    void draw() override;

};

