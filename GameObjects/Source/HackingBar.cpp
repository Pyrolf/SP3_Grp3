#include "HackingBar.h"


HackingBar::HackingBar(void)
{
	active = false;
	goingUp = false;
	speed = 0.f;
	bottomPos.SetZero();
	topPos.SetZero();
	vel.SetZero();
}

HackingBar::~HackingBar(void)
{
}

void HackingBar::Init(float speed, Vector3 bottomPos, Vector3 topPos)
{
	this->speed = speed;
	this->bottomPos = bottomPos;
	this->topPos = topPos;
	active = true;
}

void HackingBar::Update(double dt)
{
	if(active)
	{
		if(goingUp)
		{
			vel.y += speed * dt;
		}
		else 
		{
			vel.y -= speed * dt;
		}
		bottomPos += vel  * dt;
		topPos += vel  * dt;
	}
}