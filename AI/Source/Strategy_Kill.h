#pragma once
#include "Strategy.h"
#include "Vector2.h"

class CStrategy_Kill
	: public CStrategy
{
public:
	CStrategy_Kill(void);
	~CStrategy_Kill(void);

	bool Update(CMap* m_cMap, float timeDiff);
	void SetDestination(const float x, const float y);
	void GetEnemyPosition(float& x, float& y);
	void SetEnemyPosition(const float x, const float y);

	// The AI states of the enemy
	enum CURRENT_STATE
	{
		IDLE,
		REPEL,
		ATTACK,
		PATROL,
		NUM_ENEMY_STATE,
	};
	CStrategy_Kill::CURRENT_STATE GetState(void);
	void SetState(CStrategy_Kill::CURRENT_STATE);

private:
	// Enemy AI State
	CStrategy_Kill::CURRENT_STATE CurrentState;
};