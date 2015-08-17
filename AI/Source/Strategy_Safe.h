#pragma once
#include "Strategy.h"
#include "Vector2.h"

class CStrategy_Safe
	: public CStrategy
{
public:
	CStrategy_Safe(void);
	~CStrategy_Safe(void);

	bool Update(CMap* m_cMap, float timeDiff);
	void SetDestination(const float x, const float y);
	void GetEnemyPosition(float& x, float& y);
	void SetEnemyPosition(const float x, const float y);

private:
	// The Destination is the position of the target
	Vector2 theDestination;
	// The position of the enemy
	Vector2 theEnemyPosition;
};