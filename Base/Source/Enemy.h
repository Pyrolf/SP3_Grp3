#pragma once
#include "Vector2.h"
#include "Map.h"
#include "Strategy.h"

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
	void Update(CMap* m_cMap, float timeDiff);

	// Strategy
	void ChangeStrategy(CStrategy* theNewStrategy, bool bDelete=true);

	// Set Animation Invert status of the player
	void SetAnimationInvert(bool ENEMYAnimationInvert);
	// Get Animation Invert status of the player
	bool GetAnimationInvert(void);
	// Set Animation Counter of the player
	void SetAnimationCounter(float ENEMYAnimationCounter);
	// Get Animation Counter of the player
	float GetAnimationCounter(void);
	
	enum CURRENT_STRATEGY
	{
		NIL,
		KILL,
		SAFE,
		NUM_OF_STRATEGY,
	};

	CEnemy::CURRENT_STRATEGY GetCurrentStrategy(void);
	void SetCurrentStrategy(CEnemy::CURRENT_STRATEGY currentStrategy);
	
	float GetInitialPos_x(void);
	float GetInitialPos_y(void);
	
	float GetFinalPos_x(void);
	float GetFinalPos_y(void);

	void SetKilledHero(bool killedHero);
	bool GetKilledHero(void);

private:
	// ENEMY's information
	Vector2 theENEMYPosition;
	Vector2 theENEMYInitialPosition;
	Vector2 theENEMYFinalPosition;

	bool enemyAnimationInvert;
	float enemyAnimationCounter;

	// The Destination is the position of the Hero
	Vector2 theDestination;

	CStrategy* theStrategy;

	CEnemy::CURRENT_STRATEGY currentStrategy;

	bool killedHero;
};