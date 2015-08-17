#pragma once

#include "Goodies.h"
#include "Coin.h"
#include "Health.h"

typedef int GoodiesID;
#define COIN 0
#define HEALTH 1

class CGoodiesFactory
{
public:
	CGoodiesFactory(void);
	~CGoodiesFactory(void);

	
	CGoodies* Create(GoodiesID);
};

