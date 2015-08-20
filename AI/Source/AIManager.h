#pragma once
#include "Enemy.h"
#include "Mesh.h"

#include <vector>

using std::vector;

class CAIManager
{
public:
	CAIManager();
	~CAIManager();

	vector<CEnemy*> enemiesList;
	
	void generateEnemies(CMap *map);
	CEnemy* CheckColisionBetweenEnemies(CEnemy* enemy, int tileSize);

	void Reset(void);

	std::vector<Mesh*> frontMeshes;
	std::vector<Mesh*> backMeshes;
	std::vector<Mesh*> sideMeshes;
	Mesh* alertSign;
};