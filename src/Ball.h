#pragma once
#include <vector>
#include "GameObject.h"
#include "Game.h"
#include "ValueGetter.h"
#include "BrickGrid.h"
#include "NumValueObserver.h"
#include "SoundPlayer.h"
#include "BallMovement.h"
#include "Collidable.h"
#include "CollidableObjectType.h"
#include "CollisionObserver.h"
#include "GameObjectRenderer.h"

using namespace sf;

class Ball : public GameObject, public CollisionObserver
{
private: 

    // ************************* REFERENCES *************************
    BrickGrid& grid;
   
    // ************************* OBSERVERS *************************
    std::vector<NumValueObserver*> valueObservers;
    void notifyObservers(int value);

    // ************************* PRIVATE STATE ************************
    BallMovement ballMovement;
    GameObjectRenderer renderer;
    Collidable collidable;

    Vector2f ballSize{ 0.35f, 0.35f };
    bool shouldBounce;
    bool lostLife;

    SoundPlayer soundPlayer;

    // ************************* PRIVATE FUNCTIONS ************************ 
    void checkWindowCollision();
    void checkBallLife();

    // ************************* PUBLIC FUNCTIONS ************************
public:
    Ball(Game& gameRef);

    // inherited via GameObject
    void init() override;
    void update(float deltaTime) override;
    void draw() override;
    void registerForCollision() override;

    void resetBallPosition();
    void toggleBounce();
    bool getShouldBounce() { return shouldBounce; }

    void attachObserver(NumValueObserver* observer);   
       
    // Inherited via CollisionObserver
    virtual void onCollision(Collidable& collidedObject) override;
};



