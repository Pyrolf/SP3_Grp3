#pragma once
#include "Vector3.h"
#include "Mesh.h"
#include <vector>

class GameObject
{
public:
	enum GAMEOBJECT_TYPE
	{
		WALL = 1,
		HOLE,
		DOOR,
		TOTAL_NON_ACTIVE,
		WET_FLOOR,
		TIMING_DOOR,
		LOCKED_DOOR,
		HACK_SYS,
		HEALTH,
		TOTAL
	};

	int type;
	Vector3 pos;
	int currentFrame;
	float frameTime, currentFrameTime;

	GameObject();
	GameObject(int type, Vector3 pos);
	~GameObject();
};