#pragma once
#include "Vector2.h"
#include "Map.h"

class CStrategy
{
public:
	CStrategy(void);
	~CStrategy(void);

	virtual bool Update(CMap* m_cMap, float timeDiff)=0;
	virtual void SetDestination(const float x, const float y)=0;
	virtual void GetEnemyPosition(float& x, float& y)=0;
	virtual void SetEnemyPosition(const float x, const float y)=0;

	int CalculateDistance(void);

	// The Destination is the position of the target
	Vector2 theDestination;
	// The position of the enemy
	Vector2 theEnemyPosition;
};