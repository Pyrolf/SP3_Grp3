#include "AIManager.h"

CAIManager::CAIManager()
{
}

CAIManager::~CAIManager()
{
	for(int i = 0; i < enemiesList.size(); i++)
	{
		if(enemiesList[i])
		{
			delete enemiesList[i];
			enemiesList[i] = NULL;
		}
	}
}

void CAIManager::generateEnemies(CMap *map)
{
	for(int i = 0; i < map->getNumOfTiles_MapHeight(); i ++)
	{
		for(int k = 0; k < map->getNumOfTiles_MapWidth(); k ++)
		{
			if(map->theScreenMap[i][k] == 10)
			{
				enemiesList.push_back(new CEnemy);

				enemiesList.back()->SetPos_x(k  * map->GetTileSize(), true);
				enemiesList.back()->SetPos_y((map->getNumOfTiles_MapHeight() - i - 1)  * map->GetTileSize(), true);
				enemiesList.back()->SetMaxRangeToDetect(map->GetTileSize() * 4);
				enemiesList.back()->SetAnimationCounter(0.f);
				enemiesList.back()->SetAnimationInvert(false);
			}
		}
	}
}