#pragma once
#include <SFML/System.hpp>
#include <vector>

#include "GameObject.h"
#include "Game.h"
#include "ValueGetter.h"
#include "Platform.h"
#include "BrickGrid.h"
#include "NumValueObserver.h"
#include "SoundPlayer.h"
#include "BallMovement.h"
#include "Collidable.h"
#include "CollidableObjectType.h"
#include "CollisionObserver.h"

//#include "PlayerController.h"

enum class CollisionDirection
{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};

using namespace sf;

class Ball : public GameObject, public CollisionObserver
{
private: 

    // ************************* REFERENCES *************************
    BrickGrid& grid;
    Platform& platform;
    //std::shared_ptr<PlayerController> playerController;
    std::vector<std::vector<GridData>>& gridVector;
   
    // ************************* OBSERVERS *************************
    std::vector<NumValueObserver*> valueObservers;
    void notifyObservers(int value);

    // ************************* PRIVATE STATE ************************
    BallMovement ballMovement;
    
    Texture texture;
    Sprite sprite; 
    Vector2f initialBallPosition;
    FloatRect spriteBounds;
    Vector2u windowSize;
    float topRenderBound;
    float deathZone;

    //Move to BallCollision or something
    Collidable collidable;

    sf::Vector2f ballVelocity{ -0.2f, -1.0f}; //starting values 
    float ballSpeed{ 500.0f };
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
    /// Used to make sure the same brick is not
    /// accidentally hit more than once per frame.
    /// </summary>
    void setLastCollided(std::size_t row, std::size_t col);
    void setLastCollidedToNull();

    bool checkWindowCollision();
    bool checkBallLife();
    bool checkPlatformCollision();
    void reflectOffPlatform();  
    void checkBrickCollision();
    void reflectOffBrick(FloatRect brickBounds);

    // ************************* PUBLIC FUNCTIONS ************************
public:
    Ball(Game& game, Platform& platformRef, std::vector<std::vector<GridData>>& gridDataVectorRef);

    // inherited via GameObject
    void init() override;
    void update(float deltaTime) override;
    void draw() override;
    void registerForCollision() override;

    void resetBallPosition();
    void toggleBounce();
    bool getShouldBounce() { return shouldBounce; }

    void attachObserver(NumValueObserver* observer);   
    //void setPlayerController(std::shared_ptr<PlayerController> controller);
    
    //u biti ne treba ovo? jer dohvaca preko Collidable
    FloatRect getBallSpriteGlobalBounds() { return sprite.getGlobalBounds(); }
   
    // Inherited via CollisionObserver
    virtual void onCollision(Collidable& collidedObject) override;
};



