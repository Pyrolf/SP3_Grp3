#pragma once
#include "Vector3.h"

class GameObject
{
public:
	enum GAMEOBJECT_TYPE
	{
		WALL = 1,
		HOLE,
		WET_FLOOR,
		DOOR,
		TOTAL_NON_ACTIVE,
		TIMING_DOOR,
		LOCKED_DOOR,
		HACK_SYS,
		HEALTH,
		TOTAL
	};

	int type;
	Vector3 pos;

	GameObject();
	GameObject(int type, Vector3 pos);
	~GameObject();
};