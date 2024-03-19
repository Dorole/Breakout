#include "GameObject.h"

GameObject::GameObject(Game& game)
	:window(game.getWindow()), valueGetter(game.getValueGetter())
{
}

void GameObject::onLevelChanged()
{
	init();
}