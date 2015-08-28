#include "AIManager.h"

CAIManager::CAIManager()
{
}

CAIManager::~CAIManager()
{
	for(int i = 0; i < zombieList.size(); i++)
	{
		if(zombieList[i])
		{
			delete zombieList[i];
			zombieList[i] = NULL;
		}
	}
}

void CAIManager::Reset(void)
{
	// Reset to Initial position
	for(vector<CZombie *>::iterator it = zombieList.begin(); it != zombieList.end(); ++it)
	{
		CZombie *zombie = (CZombie *)*it;
		zombie->Reset();
	}
}