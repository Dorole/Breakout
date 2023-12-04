#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "GameObject.h"
#include "ValueGetter.h"
#include "Platform.h"
#include "BrickGrid.h"
#include "NumValueObserver.h"
#include "LevelDataObserver.h"

using namespace sf;

class Ball : public GameObject, public LevelDataObserver
{
private: //move these to GameObject
    RenderWindow& window;
    ValueGetter& valueGetter;
    Texture texture;
    Sprite sprite; 
    Vector2f initialBallPosition;
    FloatRect spriteBounds;

    Platform& platform;
    BrickGrid& grid;
    std::vector<std::vector<GridData>>& gridVector;

    std::vector<NumValueObserver*> observers;
    void notifyObservers(int value);

    Vector2u windowSize;
    bool shouldBounce;
    bool lostLife;
    sf::Vector2f ballVelocity {-0.8f, -0.8f}; //set from ctr! (get from gameConfig)
    float ballSpeed = 300.0f; //set from ctr!
    bool isInCollision = false; //nepotrebno?
    
    void init();

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
    bool getShouldBounce() { return shouldBounce; }
    void checkWindowCollision();
    void checkPlatformCollision();
    void checkBrickCollision();

    void attachObserver(NumValueObserver* observer);

    // Inherited via LevelDataObserver
    virtual void onLevelChanged() override;
};

