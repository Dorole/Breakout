#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Game.h"

using namespace sf;

class BallMovement
{
private:
	RenderWindow& window;
	Platform& platform;

	
	sf::Vector2f ballVelocity{ -0.2f, -1.0f }; //starting values 
	float ballSpeed{ 500.0f };

	sf::Vector2f initialPosition;
	sf::Vector2f currentPosition;
	sf::Vector2f targetPosition;

	Vector2u windowSize;
	float deathZone;

	void updatePositionAbovePlatform();

public:
	BallMovement(Game& game, Platform& platformRef);

	void resetPosition();
	void updatePosition(const sf::Vector2f& newPosition);

	sf::Vector2f getInitialBallPosition() { return initialPosition; }
	sf::Vector2f getBallPosition() { return currentPosition; }

	//TEMP
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

	bool handleWindowCollision(const sf::FloatRect& globalBallBounds, const float& topRenderBound);
	bool ballMovedBelowPlatform(const sf::FloatRect& globalBallBounds);
};



