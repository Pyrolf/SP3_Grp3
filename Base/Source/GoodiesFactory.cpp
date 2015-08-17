#include "GoodiesFactory.h"
#include <stdlib.h>

CGoodiesFactory::CGoodiesFactory(void)
{
}


CGoodiesFactory::~CGoodiesFactory(void)
{
}


CGoodies* CGoodiesFactory::Create(GoodiesID id)
{
	CGoodies* theNewGoodies = NULL;
	switch (id)
	{
	case COIN:
		theNewGoodies = new CCoin;
		break;
	case HEALTH:
		theNewGoodies = new CHealth;
		break;
		break;
	default:
		break;
	}

	return theNewGoodies;
}