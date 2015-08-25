#pragma once
#include "MyMath.h"

class Blackout
{
public:
	bool blackout;
	float blackoutTime, blackoutTreshold, cooldown, cooldownTreshold;
	int noOfBlinks;

	Blackout(void);
	~Blackout(void);

	void Update(double dt);
};