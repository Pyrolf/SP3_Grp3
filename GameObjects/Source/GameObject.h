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
		TIMING_DOOR,
		LOCKED_DOOR,
		HACK_SYS,
		TOTAL
	};

	int type;
	bool active;
	Vector3 pos;

	GameObject(int type, Vector3 pos);
	~GameObject();
};