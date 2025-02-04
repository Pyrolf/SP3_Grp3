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
	for(int i = 0; i < UpdatableGoList.size(); i++)
	{
		UpdatableGoList[i] = NULL;
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
				ActiveGameObject* temp = (new ActiveGameObject(map->theScreenMap[i][k], Vector3(k * map->GetTileSize(), ((map->getNumOfTiles_MapHeight() - i) * map->GetTileSize()) - map->GetTileSize(), 0)));

				GoList.push_back(temp);
				UpdatableGoList.push_back(temp);

				temp = NULL;
			}
			else if(map->theScreenMap[i][k] >= (GameObject::BLOCK * 10) && map->theScreenMap[i][k] < (GameObject::BLOCK * 10) + 10)
			{
				ActiveGameObject* temp = (new ActiveGameObject(GameObject::BLOCK, Vector3(k * map->GetTileSize(), ((map->getNumOfTiles_MapHeight() - i) * map->GetTileSize()) - map->GetTileSize(), 0)));
				temp->id = map->theScreenMap[i][k] - (GameObject::BLOCK * 10);

				GoList.push_back(temp);
				UpdatableGoList.push_back(temp);

				temp = NULL;
			}
			else if(map->theScreenMap[i][k] >= (GameObject::HACK_SYS * 10) && map->theScreenMap[i][k] < (GameObject::HACK_SYS * 10) + 10)
			{
				ActiveGameObject* temp = (new ActiveGameObject(GameObject::HACK_SYS, Vector3(k * map->GetTileSize(), ((map->getNumOfTiles_MapHeight() - i) * map->GetTileSize()) - map->GetTileSize(), 0)));
				temp->id = map->theScreenMap[i][k] - (GameObject::HACK_SYS * 10);

				GoList.push_back(temp);
				UpdatableGoList.push_back(temp);

				temp = NULL;
			}
		}
	}

	tileSize = map->GetTileSize();
}

GameObject* GameObjectFactory::CheckColision(Vector3 pos)
{
	Vector3 min(pos.x + 1, pos.y + 1, 0);
	Vector3 max(pos.x + tileSize - 1, pos.y + tileSize - 1, 0);

	for(int i = 0; i < GoList.size(); ++i)
	{	

		if((min.x > GoList[i]->pos.x && min.x < GoList[i]->pos.x + tileSize) && (min.y > GoList[i]->pos.y && min.y < GoList[i]->pos.y + tileSize) || 
			(min.x > GoList[i]->pos.x && min.x < GoList[i]->pos.x + tileSize) && (max.y > GoList[i]->pos.y && max.y < GoList[i]->pos.y + tileSize) ||
			(max.x > GoList[i]->pos.x && max.x < GoList[i]->pos.x + tileSize) && (min.y > GoList[i]->pos.y && min.y < GoList[i]->pos.y + tileSize) ||
			(max.x > GoList[i]->pos.x && max.x < GoList[i]->pos.x + tileSize) && (max.y > GoList[i]->pos.y && max.y < GoList[i]->pos.y + tileSize))
		{
			return GoList[i];
		}

	}
	return NULL;
}

void GameObjectFactory::ResetUGO()
{
	for(int i = 0; i < UpdatableGoList.size(); ++i)
	{
		UpdatableGoList[i]->Reset();
	}
}