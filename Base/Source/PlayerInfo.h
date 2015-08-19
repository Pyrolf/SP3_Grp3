#pragma once
#include "Vector3.h"
#include "Map.h"
#include "Mesh.h"
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
	void SetPos_x(int pos_x);
	// Set position y of the player
	void SetPos_y(int pos_y);
	// Set initial position x of the player
	void SetInitialPos_x(int pos_x);
	// Set initial position y of the player
	void SetInitialPos_y(int pos_y);

	// Update Movements
	void MoveUpDown(const bool mode, const float timeDiff, CMap* m_cMap);
	void MoveLeftRight(const bool mode, const float timeDiff, CMap* m_cMap);

	// Get position x of the player
	int GetPos_x(void);
	// Get position y of the player
	int GetPos_y(void);

	// Hero Update
	void HeroUpdate(CMap* m_cMap, float timeDiff);

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
	void SetAnimationCounter(int heroAnimationCounter);
	// Get Animation Counter of the player
	int GetAnimationCounter(void);
	void Reset(void);
	
	std::vector<Mesh*> frontMeshes;
	std::vector<Mesh*> backMeshes;
	std::vector<Mesh*> sideMeshes;
private:
	// Hero's information
	Vector3 theHeroPosition;
	Vector3 theHeroInitialPosition;

	float movementSpeed;

	int health;

	CPlayerInfo::CURRENT_STATE currentState;

	float timeElasped;

	ANIMATION_DIRECTION heroAnimationDirection;
	bool heroAnimationInvert;
	float heroAnimationCounter;
};