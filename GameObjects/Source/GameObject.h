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
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		TOTAL_NON_ACTIVE,
		WET_FLOOR,
		TIMING_DOOR,
		LOCKED_DOOR,
		HACK_SYS,
		HEALTH_PACK,
		FIRE,
		TOTAL
	};

	int type;
	Vector3 pos;
	int currentFrame;
	
	GameObject();
	GameObject(int type, Vector3 pos);
	virtual ~GameObject();

	bool CheckColision(Vector3 pos, int tileSize);
};