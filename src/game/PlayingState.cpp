#include "PlayingState.h"
#include "objects/BrickGridVisual.h"
#include "objects/Platform.h"


PlayingState::PlayingState(Game& gameRef)
	: game(gameRef), GameState(gameRef), grid(gameRef.getGrid()), collisionManager(gameRef.getCollisionManager())
{
	grid.attachGridObserver(this);
}

void PlayingState::init()
{
	auto gridVisual = std::make_unique<BrickGridVisual>(game);
	auto platform = std::make_unique<Platform>(game);
	auto ball_ptr = std::make_unique<Ball>(game);
	
	ball_ptr->attachObserver(this);
	ball = ball_ptr.get();

	gameObjects.push_back(std::move(gridVisual));
	gameObjects.push_back(std::move(platform));
	gameObjects.push_back(std::move(ball_ptr));

	uiManager = std::make_unique<UIManager>(window, game);
	uiManager->attachInteractionObserver(this);
	attachValueObserver(uiManager.get());
}

void PlayingState::onStateEnter()
{
	setBackground(valueGetter.getBackgroundTexturePath());

	totalScore = 0;
	currentLives = maxLives;
	gameStarted = false;
	paused = false;

	for (const auto& observer : valueObservers)
	{
		observer->onValueChanged(totalScore, ValueType::SCORE);
		observer->onValueChanged(currentLives, ValueType::LIVES);
	}

	audioPlayer.loadPlayMusic(AudioType::LEVEL_MUSIC);

	for (auto& gameObject : gameObjects)
		gameObject->preconfigure();

	for (auto& gameObject : gameObjects)
		gameObject->init();

	collisionManager.mapCollidables();
}

void PlayingState::handleInput(sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		startGame();

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		handlePause();
	
	uiManager->handleInput(event);
}

void PlayingState::update(float deltaTime)
{
	uiManager->update();

	if (paused) return;

	updateGameObjects(deltaTime);
	checkForStateExit();
}

void PlayingState::draw()
{
	window.draw(bgImage);

	for (auto& gameObject : gameObjects)
		gameObject->draw();

	uiManager->draw();
}

void PlayingState::onStateExit()
{
	restartGame();
	audioPlayer.stopMusic();
	collisionManager.handleLevelExit(CollidableObjectType::BRICK);
}

void PlayingState::startGame()
{
	if (gameStarted || currentLives == 0 || paused) return;

	ball->activateBall();
	gameStarted = true;
}

void PlayingState::restartGame()
{
	ball->resetBall();
}

void PlayingState::handlePause()
{
	paused = !paused;
	uiManager->togglePause();
}

void PlayingState::updateScore(int amount)
{
	totalScore += amount;
}

void PlayingState::updateLives(int amount)
{
	currentLives -= amount;
}

void PlayingState::handleLostLife(int value)
{
	gameStarted = false;
	updateLives(value);
	restartGame();

	for (const auto& observer : valueObservers)
		observer->onValueChanged(currentLives, ValueType::LIVES);
}

void PlayingState::updateGameObjects(float deltaTime)
{
	//sectioned deltaTime, otherwise it's too fast - the ball sometimes 
	//registers the same collision multiple times in the same frame
	int subSteps = 4;
	float subdeltaTime = deltaTime / subSteps;

	for (int i = 0; i < subSteps; ++i)
	{
		for (auto& gameObject : gameObjects)
			gameObject->update(subdeltaTime);

		collisionManager.update(subdeltaTime);
	}
}

void PlayingState::checkForStateExit()
{
	if (currentLives == 0)
	{
		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::GAME_OVER);
	}

	if (grid.allBricksDestroyed())
	{
		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::LEVEL_CLEAR);
	}
}


void PlayingState::attachValueObserver(HUDObserver* observer)
{
	valueObservers.push_back(observer);
}

void PlayingState::attachStateObserver(StateObserver* observer)
{
	stateObservers.push_back(observer);
}

void PlayingState::onBrickDestroyed(Brick& brick)
{
	updateScore(brick.getBreakScore());

	for (const auto& observer : valueObservers)
		observer->onValueChanged(totalScore, ValueType::SCORE);
}

void PlayingState::onValueChanged(int value, ValueType valueType)
{
	if (valueType != ValueType::LIVES) return;
	handleLostLife(value);
	
}

void PlayingState::onInteract(InteractionType interactionType)
{
	switch (interactionType)
	{
	case InteractionType::RESUME:
		paused = false;
		break;
	case InteractionType::MENU:
		for (const auto& observer : stateObservers)
			observer->onStateChanged(State::MAIN_MENU);
		break;
	default:
		break;
	}
}

void PlayingState::setTextElements() {}
void PlayingState::setButtonElements() {}
