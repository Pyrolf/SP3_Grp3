#pragma once
#include "Vector2.h"
#include "Map.h"
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
	// Initialise this class instance
	void Init(void);
	// Returns true if the player is on ground
	bool isOnGround(void);
	// Returns true if the player is jumping upwards
	bool isJumpUpwards(void);
	// Returns true if the player is on freefall
	bool isFreeFall(void);
	// Set the player's status to free fall mode
	void SetOnFreeFall(bool isOnFreeFall);
	// Set the player to jumping upwards
	void SetToJumpUpwards(bool isOnJumpUpwards);
	// Stop the player's movement
	void SetToStop(void);
	// Set position x of the player
	void SetPos_x(int pos_x, bool intial = false);
	// Set position y of the player
	void SetPos_y(int pos_y, bool intial = false);
	// Set Jumpspeed of the player
	void SetJumpspeed(int jumpspeed);
	// Update Movements
	void MoveUpDown(const bool mode, const float timeDiff, CMap* m_cMap);
	void MoveLeftRight(const bool mode, const float timeDiff, CMap* m_cMap);
	// Get position x of the player
	int GetPos_x(void);
	// Get position y of the player
	int GetPos_y(void);
	// Get Jumpspeed of the player
	int GetJumpspeed(void);
	// Get mapOffset_x
	int GetMapOffset_x(void);
	// Get mapOffset_y
	int GetMapOffset_y(void);
	// Get mapFineOffset_x
	int GetMapFineOffset_x(void);
	// Get mapFineOffset_y
	int GetMapFineOffset_y(void);
	// Update Jump Upwards
	void UpdateJumpUpwards();
	// Update FreeFall
	void UpdateFreeFall();
	// Hero Update
	void HeroUpdate(CMap* m_cMap, float timeDiff);

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

	// Set Movement Speed of the player
	void SetMovementSpeed(float movementSpeed);
	// Get Movement Speed of the player
	float GetMovementSpeed(void);
	// Constrain the position of the Hero to within the border
	void ConstrainHero(const int leftBorder, const int rightBorder,
		const int topBorder, const int bottomBorder,
		float timeDiff, CMap* m_cMap);
	// Check for collision of hero with obstacles in a certain place
	int CheckCollision(float pos_x, float pos_y,
		bool m_bCheckUpwards, bool m_bCheckDownwards,
		bool m_bCheckLeft, bool m_bCheckRight, CMap* m_cMap, bool isHero = true);

	void Reset(void);
	
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

	void SetNoOfCoins(int noOfCoins);
	int GetNoOfCoins(void);
	void SetNoOfLives(int noOfLives);
	int GetNoOfLives(void);
	void SetSideView(bool sideView);
	bool GetSideView(void);

private:
	// Hero's information
	Vector2 theHeroPosition;
	Vector2 theHeroInitialPosition;
	int jumpspeed;
	bool hero_inMidAir_Up;
	bool hero_inMidAir_Down;

	ANIMATION_DIRECTION heroAnimationDirection;
	bool heroAnimationInvert;
	float heroAnimationCounter;

	float movementSpeed;
	// For scrolling.
	int mapOffset_x, mapOffset_y;
	int mapFineOffset_x, mapFineOffset_y;
	int mapOffset_yBeforeJump;

	CPlayerInfo::CURRENT_STATE currentState;
	float timeElasped;
	int noOfCoins;
	int noOfLives;
	int sideView;
};