#pragma once
#include "Enemy.h"

#include <vector>

using std::vector;

class AI
{
public:
	AI();
	~AI();

	vector<CEnemy*> enemiesList;
	bool CheckColisionBetweenEnemies(CEnemy* enemy);
};