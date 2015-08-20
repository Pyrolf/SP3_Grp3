#pragma once
#include "Vector3.h"
#include "Map.h"
#include "Mesh.h"
#include "AIManager.h"

class CPlayerInfo
{
public:
	CPlayerInfo(void);
	~CPlayerInfo(void);
	enum GEOMETRY_TYPE
	{
		GEO_TILEHERO_FRAME0,
		GEO_TILEHERO_FRAME1,
		GEO_TILEHERO_FRAME2,
		GEO_TILEHERO_FRAME3,
		NUM_GEOMETRY,
	};
	
	// Set position x of the player
	void SetPos_x(float pos_x);
	// Set position y of the player
	void SetPos_y(float pos_y);
	// Set initial position x of the player
	void SetInitialPos_x(float pos_x);
	// Set initial position y of the player
	void SetInitialPos_y(float pos_y);
	// Set target position x of the player
	void SetTargetPos_x(float pos_x);
	// Set target position y of the player
	void SetTargetPos_y(float pos_y);

	// Update Movements
	void MoveUpDown(const bool mode, const float timeDiff, CMap* m_cMap);
	void MoveLeftRight(const bool mode, const float timeDiff, CMap* m_cMap);

	// Get position x of the player
	float GetPos_x(void);
	// Get position y of the player
	float GetPos_y(void);
	// Get target position x of the player
	float GetTargetPos_x(void);
	// Get target position y of the player
	float GetTargetPos_y(void);

	// Hero Update
	void HeroUpdate(float timeDiff, CAIManager* ai_manager, GameObjectFactory* go_manager);

	// Set Movement Speed of the player
	void SetMovementSpeed(float movementSpeed);
	// Get Movement Speed of the player
	float GetMovementSpeed(void);
	
	
	enum CURRENT_STATE
	{
		NIL,
		PLAYING,
		EXITING,
		DYING,
		NUM_OF_STATES,
	};
	void SetCurrentState(CPlayerInfo::CURRENT_STATE currentState);
	CPlayerInfo::CURRENT_STATE GetCurrentState(void);

	
	void SetTimeElasped(float timeElasped);
	float GetTimeElasped(void);

	void SetHealth(int health);
	int GetHealth(void);

	enum ANIMATION_DIRECTION
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NUM_OF_DIRECTION,
	};
	
	// Set Animation Direction status of the player
	void SetAnimationDirection(ANIMATION_DIRECTION heroAnimationDirection);
	// Get Animation Direction status of the player
	ANIMATION_DIRECTION GetAnimationDirection(void);
	// Set Animation Invert status of the player
	void SetAnimationInvert(bool heroAnimationInvert);
	// Get Animation Invert status of the player
	bool GetAnimationInvert(void);
	// Set Animation Counter of the player
	void SetAnimationCounter(float heroAnimationCounter);
	// Get Animation Counter of the player
	float GetAnimationCounter(void);
	void Reset(void);
	
	// Set DeathRotate of the player
	void SetDeathRotate(float deathRotate);
	// Get Death Rotate of the player
	float GetDeathRotate(void);
	
	void knockBackEnabled(Vector3 knockBackPos);
	void knockingBack(float timeDiff);
	bool GetIsKnockingBack();
	
	void attackingEnabled(Vector3 attackTargetPos);
	void Attacking(float timeDiff, CAIManager* ai_manager, GameObjectFactory* go_manager);
	bool GetIsAttacking();

	std::vector<Mesh*> frontMeshes;
	std::vector<Mesh*> backMeshes;
	std::vector<Mesh*> sideMeshes;
	std::vector<Mesh*> deathMeshes;
	std::vector<Mesh*> attackFrontMeshes;
	std::vector<Mesh*> attackBackMeshes;
	std::vector<Mesh*> attackSideMeshes;
private:
	// Hero's information
	Vector3 theHeroPosition;
	Vector3 theHeroInitialPosition;
	Vector3 theHeroTargetPosition;

	float movementSpeed;

	int health;

	float deathRotate;

	CPlayerInfo::CURRENT_STATE currentState;

	float timeElasped;

	ANIMATION_DIRECTION heroAnimationDirection;
	bool heroAnimationInvert;
	float heroAnimationCounter;
	int heroAnimationSpeed;
	
	// For KnockBack
	bool isKnockingBack;
	Vector3 knockBackPos;

	// For KnockBack
	bool isAttacking;
	Vector3 attackTargetPos;
};