#pragma once

enum class ValueType
{
	SCORE,
	LIVES,
	LEVEL
};

class HUDObserver
{
public:
	virtual void onValueChanged(int value, ValueType valueType) = 0;
};
