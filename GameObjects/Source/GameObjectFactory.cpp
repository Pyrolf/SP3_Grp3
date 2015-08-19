#include "GameObjectFactory.h"

GameObjectFactory::GameObjectFactory()
	:
	tileSize(0)
{
}
GameObjectFactory::~GameObjectFactory()
{
	for(int i = 0; i < GoList.size(); i++)
	{
		if(GoList[i])
		{
			delete GoList[i];
			GoList[i] = NULL;
		}
	}
}

void GameObjectFactory::generateGO(CMap *map)
{
	for(int i = 0; i < map->getNumOfTiles_MapHeight(); i ++)
	{
		for(int k = 0; k < map->getNumOfTiles_MapWidth(); k ++)
		{
			if(map->theScreenMap[i][k] > 0 && map->theScreenMap[i][k] < GameObject::TOTAL_NON_ACTIVE)
			{
				GoList.push_back(new GameObject(map->theScreenMap[i][k], Vector3(k * map->GetTileSize(), ((map->getNumOfTiles_MapHeight() - i) * map->GetTileSize()) - map->GetTileSize(), 0)));
			}
			else if(map->theScreenMap[i][k] > GameObject::TOTAL_NON_ACTIVE && map->theScreenMap[i][k] < GameObject::TOTAL)
			{
				GoList.push_back(new ActiveGameObject(map->theScreenMap[i][k], Vector3(k * map->GetTileSize(), ((map->getNumOfTiles_MapHeight() - i) * map->GetTileSize()) - map->GetTileSize(), 0)));
			}
		}
	}

	tileSize = map->GetTileSize() - 2;
}

GameObject* GameObjectFactory::CheckColision(Vector3 pos)
{
	Vector3 temp1, temp2;
	float distSquared;

	for(int i = 0; i < GoList.size(); ++i)
	{
		temp1.Set(pos.x, 0, 0);
		temp2.Set(GoList[i]->pos.x, 0, 0);
		distSquared = (temp1 - temp2).LengthSquared();
		
		if(distSquared < tileSize * tileSize)
		{
			temp1.Set(0, pos.y, 0);
			temp2.Set(0, GoList[i]->pos.y, 0);
			distSquared = (temp1 - temp2).LengthSquared();

			if(distSquared < tileSize * tileSize)
			{
				return GoList[i];
			}
		}
	}
	return NULL;

	/*Vector3 min(pos.x + 1, pos.y + 1, 0);
	Vector3 max(pos.x + tileSize - 1, pos.y + tileSize - 1, 0);
		
		
	if((min.x > GoList[i]->pos.x && min.x < GoList[i]->pos.x + tileSize) && (min.y > GoList[i]->pos.y && min.y < GoList[i]->pos.y + tileSize) || 
		(min.x > GoList[i]->pos.x && min.x < GoList[i]->pos.x + tileSize) && (max.y > GoList[i]->pos.y && max.y < GoList[i]->pos.y + tileSize) ||
		(max.x > GoList[i]->pos.x && max.x < GoList[i]->pos.x + tileSize) && (min.y > GoList[i]->pos.y && min.y < GoList[i]->pos.y + tileSize) ||			(max.x > GoList[i]->pos.x && max.x < GoList[i]->pos.x + tileSize) && (max.y > GoList[i]->pos.y && max.y < GoList[i]->pos.y + tileSize))
	{
		return GoList[i];
	}*/	
}

