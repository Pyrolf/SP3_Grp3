#pragma once
#include "NormalZombie.h"
#include "SmartZombie.h"
#include "TankZombie.h"
#include "HunterZombie.h"
#include "Mesh.h"

#include <vector>

using std::vector;

class CAIManager
{
public:
	CAIManager();
	~CAIManager();

	vector<CZombie*> zombieList;
	
	void generateEnemies(CMap *map);

	void Reset(void);
};