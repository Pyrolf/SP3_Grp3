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
			if(map->theScreenMap[i][k] == 30)
			{
				enemiesList.push_back(new CEnemy);

				enemiesList.back()->SetMaxRangeToDetect(map->GetTileSize() * 5);
				enemiesList.back()->SetAnimationCounter(0.f);
				enemiesList.back()->SetAnimationInvert(false);
			}
		}
	}
}

CEnemy* CAIManager::CheckColisionBetweenEnemies(CEnemy* enemy, int tileSize)
{
	/*Vector3 min(enemy->GetPos_x() + 1, enemy->GetPos_y() + 1, 0);
	Vector3 max(enemy->GetPos_x() + tileSize - 1, enemy->GetPos_y() + tileSize - 1, 0);

	for(int i = 0; i < enemiesList.size(); ++i)
	{
		if(enemy != enemiesList[i])
		{
			if((min.x > enemiesList[i]->GetPos_x() && min.x < enemiesList[i]->GetPos_x() + tileSize) && (min.y > enemiesList[i]->GetPos_y() && min.y < enemiesList[i]->GetPos_y() + tileSize) || 
				(min.x > enemiesList[i]->GetPos_x() && min.x < enemiesList[i]->GetPos_x() + tileSize) && (max.y > enemiesList[i]->GetPos_y() && max.y < enemiesList[i]->GetPos_y() + tileSize) ||
				(max.x > enemiesList[i]->GetPos_x() && max.x < enemiesList[i]->GetPos_x() + tileSize) && (min.y > enemiesList[i]->GetPos_y() && min.y < enemiesList[i]->GetPos_y() + tileSize) ||
				(max.x > enemiesList[i]->GetPos_x() && max.x < enemiesList[i]->GetPos_x() + tileSize) && (max.y > enemiesList[i]->GetPos_y() && max.y < enemiesList[i]->GetPos_y() + tileSize))
			{
				return enemiesList[i];
			}
		}
	}*/
	return NULL;
}

void CAIManager::Reset(void)
{
	// Reset to Initial position
	for(vector<CEnemy *>::iterator it = enemiesList.begin(); it != enemiesList.end(); ++it)
	{
		CEnemy *enemy = (CEnemy *)*it;
		enemy->Reset();
	}
}