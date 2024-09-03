#pragma once

class UIDGenerator
{
private:
	static int id;

public:
	static int GetUniqueId()
	{
		return id++;
	}
};


