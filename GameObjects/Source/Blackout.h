#pragma once
#include "MyMath.h"

class Blackout
{
public:
	bool /*blackout,*/ lightOn, fullyCharged;
	float /*blackoutTime, blackoutTreshold,*/ cooldown, cooldownTreshold;
	/*int noOfBlinks;*/
	double battery, lightSize;

	Blackout(void);
	~Blackout(void);

	void Update(double dt);
	void Reset();
};