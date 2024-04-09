#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameObjectData.h"

using namespace sf;

class BallMovement
{
private:
	RenderWindow& window;
	GameObjectData& platformData;
	
	sf::Vector2f ballVelocity{ -0.2f, -1.0f }; //starting values 
	float ballSpeed{ 500.0f };

	sf::Vector2f initialPosition;
	sf::Vector2f currentPosition;
	sf::Vector2f targetPosition;

	Vector2u windowSize;
	float deathZone;

	void updatePositionAbovePlatform();

public:
	BallMovement(Game& game);

	void resetPosition();
	void updatePosition(const sf::Vector2f& newPosition);

	sf::Vector2f getInitialBallPosition() { return initialPosition; }
	sf::Vector2f getBallPosition() { return currentPosition; } //mozda salji preko Ball?

	//TEMP
	sf::Vector2f getBallVelocity() { return ballVelocity; }
	void adjustBallVelocity(sf::Vector2f val) {
		ballVelocity = val;
	} //END TEMP

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



