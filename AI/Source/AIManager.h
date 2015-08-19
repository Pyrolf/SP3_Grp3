#pragma once
#include "Enemy.h"

#include <vector>

using std::vector;

class CAIManager
{
public:
	CAIManager();
	~CAIManager();

	vector<CEnemy*> enemiesList;
	
	void generateEnemies(CMap *map);
	bool CheckColisionBetweenEnemies(CEnemy* enemy);
};