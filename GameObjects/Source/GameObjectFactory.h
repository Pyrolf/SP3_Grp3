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

	std::vector<Mesh*> wallMesh, HoleMesh, HealthMesh, doorMesh, wetFloorMesh, timmingDoorMesh, lockedDoorMesh, hackMesh;

	GameObjectFactory();
	~GameObjectFactory();

	void generateGO(CMap *map);
	GameObject* CheckColision(Vector3 pos);
};