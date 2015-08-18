#include"Map.h"
#include"GameObject.h"
#include<vector>

using std::vector;

class GameObjectFactory
{
public:
	vector<GameObject*> GoList;
	int tileSize;

	GameObjectFactory();
	~GameObjectFactory();

	void generateGO(CMap *map);
	GameObject* CheckColision(Vector3 pos);
};