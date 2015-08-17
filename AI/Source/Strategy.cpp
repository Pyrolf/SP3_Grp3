#include "Strategy.h"
#include <iostream>

using namespace std;

CStrategy::CStrategy()
{
}

CStrategy::~CStrategy()
{
}

bool CStrategy::Update(CMap* m_cMap, float timeDiff)
{
	cout << "void CStrategy::Update()" << endl;
	return false;
}

int CStrategy::CalculateDistance(void)
{
	return ((theDestination.x - theEnemyPosition.x) * (theDestination.x - theEnemyPosition.x) +
		(theDestination.y - theEnemyPosition.y) * (theDestination.y - theEnemyPosition.y));
}