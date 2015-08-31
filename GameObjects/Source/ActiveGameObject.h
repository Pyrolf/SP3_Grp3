#pragma once
#include "gameobject.h"

class ActiveGameObject : public GameObject
{
public:
	int id;
	bool active, canActivate;
	float frameTime, currentFrameTime;

	ActiveGameObject();
	ActiveGameObject(int type, Vector3 pos);
	virtual ~ActiveGameObject();

	void update(double dt);
	void InitRanodmVars();
	void Reset();
};