#pragma once
#include"Vector3.h"

class HackingBar
{
public:
	bool active, goingUp;
	float speed;
	Vector3 bottomPos, topPos, vel;

	HackingBar(void);
	~HackingBar(void);

	void Init(float speed, Vector3 bottomPos, Vector3 topPos);
	void Update(double dt);
};

