#pragma once
#include <SFML/Graphics.hpp>
#include "game/Game.h"
#include "GameObject.h"
#include "collision/Collidable.h"
#include "utils/ValueGetter.h"
#include "collision/CollidableObjectType.h"
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

    static const float PLATFORM_BOTTOM_OFFSET;
    static const float PLATFORM_SPEED;
    bool windowBoundReached = false;

    // ************************* PRIVATE FUNCTIONS ************************

    void setInitialPlatformPosition();
    void movePlatform(float deltaTime);

    // ************************* PUBLIC FUNCTIONS ************************
public:
    Platform(Game& game);

    // inherited via GameObject
    void preconfigure() override;
    void init() override;
    void update(float deltaTime) override;
    void draw() override;
    void registerForCollision() override;

    Vector2f getInitialPlatformPosition() { return initialPlatformPosition; }
    bool platformWindowBoundReached() { return windowBoundReached; }
};


