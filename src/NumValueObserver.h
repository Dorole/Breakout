#pragma once

enum class ValueType
{
	SCORE,
	LIVES
};

class NumValueObserver
{
public:
	virtual void onValueChanged(int value, ValueType valueType) = 0;
};