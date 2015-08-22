#pragma once
#include "Vector3.h"
#include "Map.h"
#include "PosNode.h"

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

	// Reset this class instance
	void Reset(void);

	// Set position x of the enemy
	void SetPos_x(float pos_x);
	// Set position y of the enemy
	void SetPos_y(float pos_y);
	// Set position of the enemy
	void SetPos(Vector3 pos);

	// Set initial position node of the enemy
	void SetInitialPosNode(CPosNode* posNode);
	// Set current position node of the enemy
	void SetCurrentPosNode(CPosNode* posNode);
	// Set target position node of the enemy
	void SetTargetPosNode(CPosNode* posNode);

	// Get position of the enemy
	Vector3 GetPos(void);
	// Get current position node of the enemy
	CPosNode* GetCurrentPosNode(void);
	// Get target position node of the enemy
	CPosNode* GetTargetPosNode(void);
	
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
		NIL,
		ATTACK,
		CHASE,
		RETURN,
		PATROL,
		IDLE,
		NUM_OF_CURRENT_MODE,
	};
	void SetCurrentMode(CURRENT_MODE currentMode);
	CURRENT_MODE GetCurrentMode(void);

	void SetHitHero(bool hitHero);
	bool GetHitHero(void);

	void SetMaxRangeToDetect(int maxRangeToDetect);
	int GetMaxRangeToDetect(void);
	
	// Check current mode
	void CheckMode(CPosNode* heroPosNode, int tileSize);

	// Choose patrol or idle mode
	void ChoosePatrolOrIdleMode(void);

	// ENEMY Update
	void Update(int tileSize, float timeDiff, CPosNode* heroPosNode);

	void moving(float timeDiff);
	void CalculateVel(void);

	void UpdateAnimation(Vector3 CurrentPos, Vector3 PrevPos, float timeDiff);
	
	vector<CPosNode*> PathFinding(CPosNode* TargetPosNode, int tileSize);

	bool ifNodeInList(CPosNode* posNode, vector<CPosNode*> list);
	void storeAdjacentNodeInList(CPosNode* posNode, vector<CPosNode*>* openList, vector<CPosNode*>* closedList);

	int Calculate_G(CPosNode* posNode, vector<CPosNode*> list);
	int Calculate_H(CPosNode* CurrentPosNode, CPosNode* TargetPosNode, float tileSize);

	int Calculate_F(CPosNode* CurrentPosNode, CPosNode* TargetPosNode, float tileSize, vector<CPosNode*> list);

private:
	// ENEMY's information
	Vector3 theENEMYPosition;
	CPosNode* theENEMYInitialPosNode;
	CPosNode* theENEMYCurrentPosNode;
	CPosNode* theENEMYTargetPosNode;
	Vector3 vel;
	vector<CPosNode*> enemyPath;
	
	float movementSpeed;

	float time;

	CURRENT_MODE currentMode;

	int maxRangeToDetect;

	bool enemyAnimationInvert;
	float enemyAnimationCounter;

	bool hitHero;
	ANIMATION_DIRECTION enemyAnimationDirection;
};