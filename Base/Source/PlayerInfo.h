#pragma once
#include "Mesh.h"
#include "LevelMap_Nodes.h"

class CPlayerInfo
{
public:
	CPlayerInfo(void);
	~CPlayerInfo(void);

	void Reset(void);

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
	// Set position of the player
	void SetPos(Vector3 pos);

	// Set initial position node of the player
	void SetInitialPosNode(CPosNode* posNode);
	// Set current position node of the player
	void SetCurrentPosNode(CPosNode* posNode);
	// Set target position node of the player
	void SetTargetPosNode(CPosNode* posNode);

	// Get position of the player
	Vector3 GetPos(void);
	// Get current position node of the player
	CPosNode* GetCurrentPosNode(void);
	// Get target position node of the player
	CPosNode* GetTargetPosNode(void);
	
	enum CURRENT_STATE
	{
		NIL,
		MOVING,
		ATTACKING,
		KNOCKED_BACKING,
		EXITING,
		SLIDING,
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
	float GetDropScale();

	// Set just got damged of the player
	void SetJustGotDamged(bool justGotDamged);
	// Get just got damged of the player
	bool GetJustGotDamged(void);
	// Set Render Hero of the player
	void SetRenderHero(bool RenderHero);
	// Get Render Hero of the player
	bool GetRenderHero(void);
	// Set unrender or render time left of the player
	void SetUnrenderOrRenderTimeLeft(float unrenderOrRenderTimeLeft);
	// Get unrender or render time left of the player
	float GetUnrenderOrRenderTimeLeft(void);

	// Set mapOffset of the player
	void SetMapOffset(Vector3 mapOffset);
	// Get mapOffset of the player
	Vector3 GetMapOffset(void);

	// Update Movements
	void MoveUpDown(const bool mode, CAIManager* ai_manager, int tileSize);
	void MoveLeftRight(const bool mode, CAIManager* ai_manager, int tileSize);

	// Hero Update
	void HeroUpdate(float timeDiff, CAIManager* ai_manager, GameObjectFactory* go_manager, CMap* map);

	void knockBackEnabled(Vector3 AI_Pos, CAIManager* ai_manager, int tileSize);

	void moving(float timeDiff, CMap* map);
	void moveAnimation(float timeDiff, Vector3 prevPos);
	
	void attackingEnabled();
	void Attacking(float timeDiff, CAIManager* ai_manager, GameObjectFactory* go_manager);
	
	bool CheckCollisionTarget(CAIManager* ai_manager, int tileSize);
	bool CheckCollisionCurrent(void);
	void CollisionResponseCurrent(void);

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
	CPosNode* theHeroInitialPosNode;
	CPosNode* theHeroCurrentPosNode;
	CPosNode* theHeroTargetPosNode;
	Vector3 vel;

	float movementSpeed;

	int health;

	CPlayerInfo::CURRENT_STATE currentState;

	float timeElasped;

	ANIMATION_DIRECTION heroAnimationDirection;
	bool heroAnimationInvert;
	float heroAnimationCounter;
	float holeDropScale;
	int heroAnimationSpeed;
	
	bool justGotDamged;
	bool RenderHero;
	float unrenderOrRenderTimeLeft;

	Vector3 mapOffset;
};