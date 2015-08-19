#pragma once
#include "gameobject.h"

class ActiveGameObject : public GameObject
{
public:
	bool active;
	float currentFrame;
	int random; // for any use depending on the gameObject

	ActiveGameObject();
	ActiveGameObject(int type, Vector3 pos);
	~ActiveGameObject();

	void update(double dt);
};