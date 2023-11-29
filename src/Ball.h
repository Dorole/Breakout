#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ValueGetter.h"
#include "Platform.h"
#include "BrickGrid.h"

using namespace sf;

class Ball : public GameObject
{
private: //move these to GameObject
    RenderWindow& window;
    ValueGetter& valueGetter;
    Texture texture;
    Sprite sprite; //circle shape?
    Vector2f initialBallPosition;
    FloatRect spriteBounds;

    Platform& platform;
    BrickGrid& grid;
    std::vector<std::vector<GridData>>& gridVector;


    Vector2u windowSize;
    bool shouldBounce;
    sf::Vector2f ballVelocity {-0.8f, -0.8f}; //set from ctr! (from value getter or similar)
    float ballSpeed = 400.0f; //set from ctr!
    bool isInCollision = false;
    

    //move these to GameObject
    void setSpriteOriginToCenter();
    void getSpriteBounds();
  
    /// <summary>
    /// Moves the ball relative to the mouse position 
    /// and relative to the platform position before the game starts.
    /// </summary>
    void moveIdle(float deltaTime);


public:
    Ball(RenderWindow& windowRef, ValueGetter& valueGetterRef, Platform& platformRef, BrickGrid& gridRef, std::vector<std::vector<GridData>>& gridDataVectorRef);

    void update(float deltaTime) override;
    void draw() override;

    void setInitialBallPosition();
    void toggleBounce();
    void checkWindowCollision();
    void checkPlatformCollision();
    void checkBrickCollision();
};

