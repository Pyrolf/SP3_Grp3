#include "Strategy_Safe.h"
#include <iostream>

using namespace std;

CStrategy_Safe::CStrategy_Safe()
{
}

CStrategy_Safe::~CStrategy_Safe()
{
}

bool CStrategy_Safe::Update(CMap* m_cMap, float timeDiff)
{
	theEnemyPosition.x = theEnemyPosition.x + (theDestination.x - theEnemyPosition.x > 0 ? (200.0f * timeDiff) : -(200.0f * timeDiff) );
	return false;
	//theEnemyPosition.y = theEnemyPosition.y + (theDestination.y - theEnemyPosition.y > 0 ? 5 : -5 );
}

void CStrategy_Safe::SetDestination(const float x, const float y)
{
	theDestination.x = x;
	theDestination.y = y;
}

void CStrategy_Safe::GetEnemyPosition(float& x, float& y)
{
	x = theEnemyPosition.x;
	y = theEnemyPosition.y;
}

void CStrategy_Safe::SetEnemyPosition(const float x, const float y)
{
	theEnemyPosition.x = x;
	theEnemyPosition.y = y;
}