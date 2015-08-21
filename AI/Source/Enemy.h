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
	void SetTargetPosition(const int pos_x, const int pos_y);

	// Get position x of the enemy
	int GetPos_x(void);
	// Get position y of the enemy
	int GetPos_y(void);
	// Set the destination of this enemy
	int GetTargetPosition_x(void);
	// Set the destination of this enemy
	int GetTargetPosition_y(void);

	// ENEMY Update
	void Update(GameObjectFactory* goManager, float timeDiff, Vector3 heroPos);

	enum ANIMATION_DIRECTION
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NUM_OF_DIRECTION,
	};

	// Set Animation Invert status of the enemy
	void SetAnimationInvert(bool ENEMYAnimationInvert);
	// Get Animation Invert status of the enemy
	bool GetAnimationInvert(void);
	// Set Animation Counter of the enemy
	void SetAnimationCounter(float ENEMYAnimationCounter);
	// Get Animation Counter of the enemy
	float GetAnimationCounter(void);
	// Get Animation Direction status of the enemy
	ANIMATION_DIRECTION GetAnimationDirection(void);
	
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

	void SetHitHero(bool hitHero);
	bool GetHitHero(void);

	void SetMaxRangeToDetect(int maxRangeToDetect);
	int GetMaxRangeToDetect(void);

	bool CheckCollision(GameObjectFactory* goManager, Vector3 pos);

	void MoveEnemy(GameObjectFactory* goManager, float timeDiff, Vector3 target);

	void UpdateAnimation(Vector3 CurrentPos, Vector3 PrevPos, float timeDiff);
	
	void SetJustAlerted(bool justAlerted);
	bool GetJustAlerted(void);
	
	void PathFinding(GameObjectFactory* goManager);
private:
	// ENEMY's information
	Vector3 theENEMYPosition;
	Vector3 theENEMYInitialPosition;
	Vector3 theENEMYTargetPosition;
	float idleTime;

	CURRENT_MODE currentMode;

	int maxRangeToDetect;

	bool enemyAnimationInvert;
	float enemyAnimationCounter;

	bool hitHero;
	ANIMATION_DIRECTION enemyAnimationDirection;

	bool justAlerted;
	float timeAlerted;
};