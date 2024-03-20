#include "GameObject.h"

GameObject::GameObject(Game& game)
	:window(game.getWindow()), valueGetter(game.getValueGetter()), collisionManager(game.getCollisionManager())
{
}

void GameObject::onLevelChanged()
{
	init();
}