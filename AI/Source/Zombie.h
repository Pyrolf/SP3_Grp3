#pragma once
#include "Vector3.h"
#include "Map.h"
#include "PosNode.h"

class CZombie
{
public:
	CZombie(void);
	virtual ~CZombie(void);

	enum GEOMETRY_TYPE
	{
		GEO_TILEzombie_FRAME0,
		GEO_TILEzombie_FRAME1,
		GEO_TILEzombie_FRAME2,
		GEO_TILEzombie_FRAME3,
		NUM_GEOMETRY,
	};
	
	virtual void Init(CMap *map) = 0;

	// Reset this class instance
	virtual void Reset(void) = 0;

	// Set position x of the zombie
	void SetPos_x(float pos_x);
	// Set position y of the zombie
	void SetPos_y(float pos_y);
	// Set position of the zombie
	void SetPos(Vector3 pos);

	// Set initial position node of the zombie
	void SetInitialPosNode(CPosNode* posNode);
	// Set current position node of the zombie
	void SetCurrentPosNode(CPosNode* posNode);
	// Set target position node of the zombie
	void SetTargetPosNode(CPosNode* posNode);

	// Get position of the zombie
	Vector3 GetPos(void);
	// Get current position node of the zombie
	CPosNode* GetCurrentPosNode(void);
	// Get target position node of the zombie
	CPosNode* GetTargetPosNode(void);
	
	// Get velocity of the zombie
	Vector3 GetVel(void);

	// Set time of the zombie
	void SetTime(float time);
	// Get time of the zombie
	float GetTime(void);

	// Set health of the zombie
	void SetHealth(int health);
	// Get health of the zombie
	int GetHealth(void);

	enum ANIMATION_DIRECTION
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NUM_OF_DIRECTION,
	};

	// Set Animation Invert status of the zombie
	void SetAnimationInvert(bool zombieAnimationInvert);
	// Get Animation Invert status of the zombie
	bool GetAnimationInvert(void);
	// Set Animation Counter of the zombie
	void SetAnimationCounter(float zombieAnimationCounter);
	// Get Animation Counter of the zombie
	float GetAnimationCounter(void);
	// Set Animation Direction status of the zombie
	void SetAnimationDirection(ANIMATION_DIRECTION dir);
	// Get Animation Direction status of the zombie
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
	void CheckMode(CPosNode* heroPosNode, int tileSize, Vector3 heroPos);
	void ChaseCheck(CPosNode* heroPosNode, int tileSize);
	void ReturnCheck(int tileSize);
	bool AttackCheck(CPosNode* heroPosNode, Vector3 heroPos, int tileSize);
	bool checkIfHeroIsWithinSight(Vector3 heroPos);

	// Choose patrol or idle mode
	void ChoosePatrolOrIdleMode(void);

	// zombie Update
	void Update(int tileSize, float timeDiff, CPosNode* heroPosNode, Vector3 heroPos);

	void moving(float timeDiff);
	void CalculateVel(void);

	void UpdateAnimation(Vector3 CurrentPos, Vector3 PrevPos, float timeDiff);
	
	vector<CPosNode*> PathFinding(CPosNode* TargetPosNode, int tileSize);

	bool ifNodeInList(CPosNode* posNode, vector<CPosNode*> list);
	void storeAdjacentNodeInList(CPosNode* posNode, vector<CPosNode*>* openList, vector<CPosNode*>* closedList, vector<CPosNode*>* deletedList, CPosNode* TargetPosNode);

	int Calculate_G(CPosNode* posNode, vector<CPosNode*> list);
	int Calculate_H(CPosNode* CurrentPosNode, CPosNode* TargetPosNode, float tileSize);

	int Calculate_F(CPosNode* CurrentPosNode, CPosNode* TargetPosNode, float tileSize, vector<CPosNode*> list);

	bool active;

	enum ZOMBIE_TYPE
	{
		NORMAL = 0,
		SMART,
		TANK,
		HUNTER
	};
	int zombie_type;

protected:
	// zombie's information
	Vector3 theZombiePosition;
	CPosNode* theZombieInitialPosNode;
	CPosNode* theZombieCurrentPosNode;
	CPosNode* theZombieTargetPosNode;
	Vector3 vel;
	vector<CPosNode*> zombiePath; 
	
	float movementSpeed;

	float time;

	CURRENT_MODE currentMode;

	int maxRangeToDetect;

	bool zombieAnimationInvert;
	float zombieAnimationCounter;

	bool hitHero;
	ANIMATION_DIRECTION zombieAnimationDirection;
	int animationSpeed;

	int health;
};