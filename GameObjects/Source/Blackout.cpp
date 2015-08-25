#include "Blackout.h"


Blackout::Blackout(void)
{
	Math::InitRNG();
	blackout = false;
	blackoutTime = Math::RandFloatMinMax(0.5, 2);
	blackoutTreshold = 0;
	cooldown = Math::RandFloatMinMax(3, 5);
	cooldownTreshold = 0;
	noOfBlinks = 0;
}

Blackout::~Blackout(void)
{
}

void Blackout::Update(double dt)
{
	if(blackout)
	{
		blackoutTreshold+=dt;

		if(blackoutTreshold > 0.04 && noOfBlinks > 0)
		{
			blackoutTreshold = 0;
			blackout = false;
		}
		else if(blackoutTreshold > blackoutTime)
		{
			blackoutTreshold = 0;
			blackoutTime = Math::RandFloatMinMax(0.5, 2);
			blackout = false;
		}
	}
	else
	{
		cooldownTreshold += dt;
		if(noOfBlinks > 0 && cooldownTreshold > 0.05)
		{
			cooldownTreshold = 0;
			--noOfBlinks;
			blackout = true;
		}
		else if(cooldownTreshold > cooldown)
		{
			cooldownTreshold = 0;
			cooldown = Math::RandFloatMinMax(3, 5);
			noOfBlinks = Math::RandIntMinMax(2, 4);
		}
	}
}