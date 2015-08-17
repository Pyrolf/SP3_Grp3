#include"Map.h"
#include"GameObject.h"
#include<vector>

using std::vector;

vector<GameObject*> generateGO(CMap *map)
{
	vector<GameObject*> temp;

	for(int i = 0; i < map->getNumOfTiles_MapHeight(); i ++)
	{
		for(int k = 0; k < map->getNumOfTiles_MapWidth(); k ++)
		{
			if(map->theScreenMap[i][k] != 0)
			{
				temp.push_back(new GameObject(map->theScreenMap[i][k], Vector3(k * map->GetTileSize(), ((map->getNumOfTiles_MapHeight() - i) * map->GetTileSize()) - map->GetTileSize(), 0), map->GetTileSize()));
			}
		}
	}

	return temp;
}