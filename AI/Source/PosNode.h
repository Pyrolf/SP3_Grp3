#include "Vector3.h"
#include "GameObjectFactory.h"

#pragma once
class CPosNode
{
public:
	enum POS_TYPE
	{
		NONE = 0,
		WALL,
		HOLE,
		DOOR,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		TOTAL_NON_ACTIVE_GO,
		WET_FLOOR,
		TIMING_DOOR,
		BLOCK,
		HACK_SYS,
		HEALTH_PACK,
		TRAP,
		TOTAL_ACTIVE_GO,
		HERO_INIT_POS = 20,
		NORMAL_ZOMBIE_INITIAL_POS = 30,
		SMART_ZOMBIE_INITIAL_POS,
		TANK_ZOMBIE_INITIAL_POS,
		HUNTER_ZOMBIE_INITIAL_POS
	};

	CPosNode(void);
	CPosNode(Vector3 newPos, int newPosType);
	~CPosNode(void);

	Vector3 pos;
	int posType;
	
	GameObject* gameObject;
	CPosNode* parent;
	
	CPosNode *up, *down, *left, *right;
};