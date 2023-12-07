#include "GameObject.h"

GameObject::GameObject(RenderWindow& windowRef, ValueGetter& valueGetterRef)
	:window(windowRef), valueGetter(valueGetterRef)
{
}

void GameObject::onLevelChanged()
{
	init();
}
