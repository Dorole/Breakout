#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameObject.h"
#include "Collidable.h"
#include "ValueGetter.h"
#include "CollidableObjectType.h"
#include "GameObjectData.h"
#include "GameObjectRenderer.h"

using namespace sf;

class Platform : public GameObject
{
private:

    // ************************* PRIVATE STATE ************************
    Vector2f initialPlatformPosition{};

    GameObjectRenderer renderer;
    Collidable collidable;
    GameObjectData platformData;

    float platformBottomOffset = 40.0f;
    float platformSpeed{ 400.0f }; 
    bool windowBoundReached = false;

    // ************************* PRIVATE FUNCTIONS ************************
    
    void setInitialPlatformPosition();
    void movePlatform(float deltaTime);

    // ************************* PUBLIC FUNCTIONS ************************
public:
    Platform(Game& game);

    // inherited via GameObject
    void init() override;
    void update(float deltaTime) override;
    void draw() override;
    void registerForCollision() override;

    Vector2f getInitialPlatformPosition() { return initialPlatformPosition; }
    bool platformWindowBoundReached() { return windowBoundReached; } 
};

