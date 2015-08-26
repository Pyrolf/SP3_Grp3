#include "Blackout.h"

Blackout::Blackout(void)
{
	Math::InitRNG();
	blackout = false;
	blackoutTime = Math::RandFloatMinMax(4, 6);
	blackoutTreshold = 0;
	cooldown = Math::RandFloatMinMax(4, 8);
	cooldownTreshold = 0;
	noOfBlinks = 0;

	lightOn = false;
	fullyCharged;
	battery = 4;
	lightSize = 1;
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
			blackoutTime = Math::RandFloatMinMax(4, 6);
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
			cooldown = Math::RandFloatMinMax(4, 8);
			noOfBlinks = Math::RandIntMinMax(2, 4);
		}
	}

	if(lightOn && fullyCharged)
	{
		battery -= dt;
		lightSize += dt * 12;

		if(battery < 0)
		{
			battery = 0;
			lightOn = false;
			fullyCharged = false;
		}
		if(lightSize > 8)
		{
			lightSize = 8;
		}
	}
	else if(!lightOn && battery < 4 || lightSize > 1)
	{
		if(battery < 4)
		{
			battery += dt/2.5;
			if(battery > 4)
			{
				battery = 4;
				fullyCharged = true;
			}
		}
		if(lightSize > 1)
		{
			lightSize -= dt * 16;
			if(lightSize < 1)
			{
				lightSize = 1;
			}
		}
	}
}