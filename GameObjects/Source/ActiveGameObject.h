#pragma once
#include "gameobject.h"

class ActiveGameObject : public GameObject
{
public:
	bool active, canActivate;
	float frameTime, currentFrameTime;

	////////for any use depending on the gameObject////////
	int* randomInt;
	float* randomFloat;
	///////////////////////////////////////////////////////

	ActiveGameObject();
	ActiveGameObject(int type, Vector3 pos);
	virtual ~ActiveGameObject();

	void update(double dt);
	void InitRanodmVars();
};