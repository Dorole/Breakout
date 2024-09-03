#pragma once
#include <SFML/Graphics.hpp>
#include "game/Game.h"
#include "GameObjectData.h"
#include "collision/CollisionDirection.h"

using namespace sf;

class BallMovement
{
private:
	sf::RenderWindow& window;
	BrickGrid& brickGrid;
	LevelDataProvider& levelDataProvider;
	GameObjectData* platformData = nullptr;
	
	static const sf::Vector2f STARTING_BALL_VELOCITY;
	static const float BALL_SPEED;

	sf::Vector2f ballVelocity{0, 0};
	float ballSpeed{0};

	sf::Vector2f initialPosition;
	sf::Vector2f currentPosition;
	sf::Vector2f targetPosition;

	sf::Vector2u windowSize;
	float playingFieldTopBound{ 0 };
	float deathZone{ 0 };


	void updatePositionAbovePlatform();
	CollisionDirection determineCollisionDirection(const sf::FloatRect& ballBounds, const sf::FloatRect& brickBounds);

public:
	BallMovement(Game& gameRef);

	void init();
	void resetPosition();
	void updatePosition(const sf::Vector2f& newPosition);

	sf::Vector2f getInitialBallPosition() { return initialPosition; }
	sf::Vector2f getBallPosition() { return currentPosition; } 
	sf::Vector2f getBallVelocity() { return ballVelocity; }
	float getBallSpeed() { return ballSpeed; }

	/// <summary>
	/// Moves the ball relative to the mouse position 
	/// and relative to the platform position before the game starts.
	/// </summary>
	sf::Vector2f moveBallAbovePlatform();

	/// <summary>
	/// Moves the ball based on its velocity and speed.
	/// </summary>
	sf::Vector2f moveBall();

	bool handleWindowCollision(const sf::FloatRect& globalBallBounds);
	bool ballMovedBelowPlatform(const sf::FloatRect& globalBallBounds);

	void reflectOffPlatform(float hitPoint, const sf::Vector2f& collidedPosition, const sf::FloatRect& localPlatformSpriteBounds);
	void reflectOffBrick(const sf::FloatRect& ballBounds, const sf::FloatRect& brickBounds);
};




