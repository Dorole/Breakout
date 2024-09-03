#pragma once

enum class InteractionType
{
	RESUME,
	MENU,
	SOUND
};


class InteractionObserver
{
public:
	virtual void onInteract(InteractionType interactionType) = 0;
};