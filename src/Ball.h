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
    Sprite sprite; //circle shape?
    Vector2f initialBallPosition;
    FloatRect spriteBounds;

    Platform& platform;

    Vector2u windowSize;
    bool shouldBounce = false;
    sf::Vector2f ballVelocity {-0.8f, -0.8f};
    float ballSpeed = 400.0f;

    //move these to GameObject
    void setSpriteOriginToCenter();
    void getSpriteBounds();
    void setInitialBallPosition();

    /// <summary>
    /// Moves the ball relative to the mouse position 
    /// and relative to the platform position before the game starts.
    /// </summary>
    void moveIdle(float deltaTime);


public:
    Ball(RenderWindow& windowRef, ValueGetter& valueGetter, Platform& platformRef);

    void update(float deltaTime) override;
    void draw() override;

    void toggleBounce();
    void checkWindowCollision();
    void checkPlatformCollision();

};

