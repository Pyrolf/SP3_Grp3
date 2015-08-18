#pragma once
#include "Vector3.h"
#include "Map.h"
#include "GameObjectFactory.h"

class CEnemy
{
	// friend class CStrategy;
public:
	CEnemy(void);
	~CEnemy(void);

	enum GEOMETRY_TYPE
	{
		GEO_TILEENEMY_FRAME0,
		GEO_TILEENEMY_FRAME1,
		GEO_TILEENEMY_FRAME2,
		GEO_TILEENEMY_FRAME3,
		NUM_GEOMETRY,
	};

	// Initialise this class instance
	void Init(void);

	// Set position x of the enemy
	void SetPos_x(int pos_x, bool intial = false, float endPointDiff_x = 0.f);
	// Set position y of the enemy
	void SetPos_y(int pos_y, bool intial = false, float endPointDiff_y = 0.f);
	// Set the destination of this enemy
	void SetDestination(const int pos_x, const int pos_y);

	// Get position x of the enemy
	int GetPos_x(void);
	// Get position y of the enemy
	int GetPos_y(void);
	// Set the destination of this enemy
	int GetDestination_x(void);
	// Set the destination of this enemy
	int GetDestination_y(void);

	// ENEMY Update
	void Update(GameObjectFactory* goManager, float timeDiff, Vector3 heroPos);

	// Set Animation Invert status of the enemy
	void SetAnimationInvert(bool ENEMYAnimationInvert);
	// Get Animation Invert status of the enemy
	bool GetAnimationInvert(void);
	// Set Animation Counter of the enemy
	void SetAnimationCounter(float ENEMYAnimationCounter);
	// Get Animation Counter of the enemy
	float GetAnimationCounter(void);
	
	enum CURRENT_MODE
	{
		ATTACK,
		CHASE,
		RETURN,
		PATROL,
		IDLE,
		NUM_OF_CURRENT_MODE,
	};
	void SetCurrentMode(CURRENT_MODE currentMode);
	CURRENT_MODE GetCurrentMode(void);
	
	float GetInitialPos_x(void);
	float GetInitialPos_y(void);

	void SetKilledHero(bool killedHero);
	bool GetKilledHero(void);

	void SetMaxRangeToDetect(int maxRangeToDetect);
	int GetMaxRangeToDetect(void);

	bool CheckCollision(GameObjectFactory* goManager, Vector3 pos);

	void MoveEnemy(GameObjectFactory* goManager, float timeDiff, Vector3 target);

private:
	// ENEMY's information
	Vector3 theENEMYPosition;
	Vector3 theENEMYInitialPosition;
	Vector3 patrolTarget;
	float idleTime;

	CURRENT_MODE currentMode;

	int maxRangeToDetect;

	bool enemyAnimationInvert;
	float enemyAnimationCounter;

	bool killedHero;
};