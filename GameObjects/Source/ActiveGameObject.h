#pragma once
#include "gameobject.h"

class ActiveGameObject : public GameObject
{
public:
	bool active;

	ActiveGameObject();
	ActiveGameObject(int type, Vector3 pos);
	~ActiveGameObject();

	void update(double dt);
};