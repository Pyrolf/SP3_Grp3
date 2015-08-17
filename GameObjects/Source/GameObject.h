#pragma once
#include "Vector3.h"

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

class GameObject
{
public:
	int type;
	bool active;
	Vector3 pos;
	int tileSize;

	GameObject(int type, Vector3 pos, int tileSize);
	~GameObject();

	int CheckColision(Vector3 pos);
};