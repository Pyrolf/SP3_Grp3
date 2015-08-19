#include"Map.h"
#include"ActiveGameObject.h"
#include<vector>

using std::vector;

class GameObjectFactory
{
public:
	vector<GameObject*> GoList;
	vector<ActiveGameObject*> UpdatableGoList;
	int tileSize;

	GameObjectFactory();
	~GameObjectFactory();

	void generateGO(CMap *map);
	GameObject* CheckColision(Vector3 pos);
};