#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameObject.h"
#include "ValueGetter.h"
#include "Platform.h"
#include "BrickGrid.h"
#include "NumValueObserver.h"
#include "SoundPlayer.h"

using namespace sf;

class Ball : public GameObject
{
private: 

    // ************************* REFERENCES *************************
    BrickGrid& grid;
    Platform& platform;
    std::vector<std::vector<GridData>>& gridVector;
   
    // ************************* OBSERVERS *************************
    std::vector<NumValueObserver*> observers;
    void notifyObservers(int value);

    // ************************* PRIVATE STATE ************************
    Texture texture;
    Sprite sprite; 
    Vector2f initialBallPosition;
    FloatRect spriteBounds;
    Vector2u windowSize;
    int topRenderBound;

    sf::Vector2f ballVelocity{-0.5f, -0.8f}; 
    float ballSpeed{ 300.0f };
    int lastCollidedRow{ -1 };
    int lastCollidedColumn{ -1 };
    bool shouldBounce;
    bool lostLife;

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
    void setLastCollided(int row, int col);
    void setLastCollidedToNull();

    bool checkWindowCollision();
    bool checkPlatformCollision();
    bool checkBrickCollision();

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

