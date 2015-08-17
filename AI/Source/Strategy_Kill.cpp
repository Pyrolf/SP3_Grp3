#include "Strategy_Kill.h"
#include <iostream>

using namespace std;

CStrategy_Kill::CStrategy_Kill()
{
}

CStrategy_Kill::~CStrategy_Kill()
{
}

bool CStrategy_Kill::Update(CMap* m_cMap, float timeDiff)
{
	// Decide which state to change to
	int distanceHeroToEnemy = CalculateDistance();
	if(distanceHeroToEnemy < 16384.0f)
	{
		if(distanceHeroToEnemy < 1024.0f)
			CurrentState = REPEL;
		else
			CurrentState = ATTACK;
	}
	else
		CurrentState = IDLE;

	//Based on the current state, move the enemy
	switch(CurrentState)
	{
	case ATTACK:
		theEnemyPosition.x = theEnemyPosition.x + (theDestination.x - theEnemyPosition.x > 0 ? (350.0f * timeDiff) : -(350.0f * timeDiff) );
		break;
	case REPEL:
		{
			theEnemyPosition.x = theEnemyPosition.x + (theDestination.x - theEnemyPosition.x > 0 ? -(800.0f * timeDiff) : (800.0f * timeDiff) );
			return true;
		}
		break;
	default:
		// Do nothing if idling
		break;
	}
	return false;
	//theEnemyPosition.x = theEnemyPosition.x + (theDestination.x - theEnemyPosition.x > 0 ? 5 : -5 );
	//theEnemyPosition.y = theEnemyPosition.y + (theDestination.y - theEnemyPosition.y > 0 ? 5 : -5 );
}

void CStrategy_Kill::SetDestination(const float x, const float y)
{
	theDestination.x = x;
	theDestination.y = y;
}

void CStrategy_Kill::GetEnemyPosition(float& x, float& y)
{
	x = theEnemyPosition.x;
	y = theEnemyPosition.y;
}

void CStrategy_Kill::SetEnemyPosition(const float x, const float y)
{
	theEnemyPosition.x = x;
	theEnemyPosition.y = y;
}
