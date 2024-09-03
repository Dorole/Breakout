 #pragma once
#include <vector>
#include "GameObject.h"
#include "GameObjectRenderer.h"
#include "BallMovement.h"
#include "game/BrickGrid.h"
#include "game/Game.h"
#include "utils/ValueGetter.h"
#include "audio/SoundPlayer.h"
#include "collision/Collidable.h"
#include "collision/CollidableObjectType.h"
#include "events/HUDObserver.h"
#include "events/CollisionObserver.h"

using namespace sf;

class Ball : public GameObject, public CollisionObserver
{
private:

    // ************************* REFERENCES *************************
    BrickGrid& grid;
    SoundPlayer& soundPlayer;

    // ************************* OBSERVERS *************************
    std::vector<HUDObserver*> valueObservers;
    void notifyObservers(int value);

    // ************************* PRIVATE STATE ************************
    BallMovement ballMovement;
    GameObjectRenderer renderer;
    Collidable collidable;

    Vector2f ballSize{ 0.35f, 0.35f };
    bool shouldBounce;
    bool lostLife;

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

    void resetBall();
    void activateBall();
    void attachObserver(HUDObserver* observer);

    // Inherited via CollisionObserver
    virtual void onCollision(Collidable& collidedObject) override;
};




