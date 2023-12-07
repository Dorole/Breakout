#pragma once
#include <SFML/System.hpp>
#include <vector>

#include "GameObject.h"
#include "ValueGetter.h"
#include "Platform.h"
#include "BrickGrid.h"
#include "NumValueObserver.h"
#include "SoundPlayer.h"

enum class CollisionDirection
{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};

using namespace sf;

class Ball : public GameObject
{
private: 

    // ************************* REFERENCES *************************
    BrickGrid& grid;
    Platform& platform;
    std::vector<std::vector<GridData>>& gridVector;
   
    // ************************* OBSERVERS *************************
    std::vector<NumValueObserver*> valueObservers;
    void notifyObservers(int value);

    // ************************* PRIVATE STATE ************************
    Texture texture;
    Sprite sprite; 
    Vector2f initialBallPosition;
    FloatRect spriteBounds;
    Vector2u windowSize;
    float topRenderBound;
    float deathZone;

    sf::Vector2f ballVelocity{ -0.2f, -1.0f}; //starting values 
    float ballSpeed{ 450.0f };
    std::size_t lastCollidedRow{ 1000 };
    std::size_t lastCollidedColumn{ 1000 };
    bool shouldBounce;
    bool lostLife;

    CollisionDirection collisionDirection = CollisionDirection::BOTTOM; //default collision

    SoundPlayer soundPlayer;

    // ************************* PRIVATE FUNCTIONS ************************
    void setSpriteOriginToCenter();
    void getSpriteBounds();
  
    /// <summary>
    /// Moves the ball relative to the mouse position 
    /// and relative to the platform position before the game starts.
    /// </summary>
    void moveIdle(float deltaTime);

    /// <summary>
    /// Used to make sure the same brick is not
    /// accidentally hit more than once per frame.
    /// </summary>
    void setLastCollided(std::size_t row, std::size_t col);
    void setLastCollidedToNull();

    bool checkWindowCollision();
    bool checkPlatformCollision();
    void reflectOffPlatform();  
    void checkBrickCollision();
    void reflectOffBrick(FloatRect& brickBounds);

    // ************************* PUBLIC FUNCTIONS ************************
public:
    Ball(RenderWindow& windowRef, ValueGetter& valueGetterRef, Platform& platformRef, BrickGrid& gridRef, std::vector<std::vector<GridData>>& gridDataVectorRef);

    // inherited via GameObject
    void init() override;
    void update(float deltaTime) override;
    void draw() override;

    void setInitialBallPosition();
    void toggleBounce();
    bool getShouldBounce() { return shouldBounce; }

    void attachObserver(NumValueObserver* observer);   
    
};

