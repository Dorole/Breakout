#include "GameObject.h"

GameObject::GameObject(Game& game)
	: window(game.getWindow()), 
	valueGetter(game.getValueGetter()), 
	collisionManager(game.getCollisionManager()), 
	levelDataProvider(game.getLevelDataProvider())
{
}

void GameObject::onLevelChanged()
{
	init();
	//pazi ovo se zove istovremeno kad i tipa grid init() - problem ako se ovo pozove prije grida
	//potencijalno makni ovo i pozovi u PlayingState onStateEnter da bude ziher
}