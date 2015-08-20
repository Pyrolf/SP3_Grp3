#include"Map.h"
#include"ActiveGameObject.h"
#include<vector>

using std::vector;

class GameObjectFactory
{
public:
	GameObjectFactory();
	~GameObjectFactory();

	vector<GameObject*> GoList;
	vector<ActiveGameObject*> UpdatableGoList;
	int tileSize;

	void generateGO(CMap *map);
	GameObject* CheckColision(Vector3 pos);
};