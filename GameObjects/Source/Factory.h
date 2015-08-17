#pragma once

class Factory
{
public:
	Factory();
	virtual ~Factory();
	virtual void IncreaseSize() = 0;
};

