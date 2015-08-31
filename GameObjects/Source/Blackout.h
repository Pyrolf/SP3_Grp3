#pragma once
#include "MyMath.h"

class Blackout
{
public:
	bool /*blackout,*/ lightOn, fullyCharged, ableToCharge;
	float /*blackoutTime, blackoutTreshold, cooldownTreshold*/cooldown;
	/*int noOfBlinks;*/
	double battery, lightSize;

	Blackout(void);
	~Blackout(void);

	void Update(double dt);
	void Reset();
};