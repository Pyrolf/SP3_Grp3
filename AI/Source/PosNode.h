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
		TOTAL_NON_ACTIVE_GO,
		WET_FLOOR,
		TIMING_DOOR,
		LOCKED_DOOR,
		HACK_SYS,
		HEALTH_PACK,
		TOTAL_ACTIVE_GO,
		ENEMY_INITIAL_POS = 10,
		HERO_INIT_POS = 20,
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