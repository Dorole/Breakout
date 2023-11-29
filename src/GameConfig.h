#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

/// <summary>
/// Holder for const game members.
/// </summary>
class GameConfig
{
private:
	//Game general
	int maxLives = 3; //make all static const?
	
	//Grid
	int gridOffset = 6;

	//UI 
	
	//Ball 
	Vector2f ballVelocity = Vector2f(-0.8f, -0.8f);
	float ballStartSpeed = 300.0f;
	float angleVariation = 0.2f;

	//Platform 


public:
	int getMaxLives() { return maxLives; }
	int getGridOffset() { return gridOffset; }
	Vector2f getBallVelocity() { return ballVelocity; }
	float getBallStartSpeed() { return ballStartSpeed; }
	float getAngleVariation() { return angleVariation; }
};