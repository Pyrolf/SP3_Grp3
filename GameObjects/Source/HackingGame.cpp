#include "HackingGame.h"


HackingGame::HackingGame(void)
{
	active = false;
	bottomLeftPos.SetZero();
	topRightPos.SetZero();
	currentBar = 0;
	/*std::vector<HackingBar*> hackingBar;*/
}

HackingGame::~HackingGame(void)
{
	for(int i = 0; i < hackingBar.size(); ++i)
	{
		if(hackingBar[i])
		{
			delete hackingBar[i];
			hackingBar[i] = NULL;
		}
	}
}

void HackingGame::Init(Vector3 bottomLeftPos, Vector3 topRightPos)
{
	this->bottomLeftPos = bottomLeftPos;
	this->topRightPos = topRightPos;

	float distanceBetween = ((topRightPos.x - bottomLeftPos.x))/9;
	float currentX = bottomLeftPos.x + distanceBetween;
	float speed = 250;

	for(int i = 1; i < 9; ++i)
	{
		hackingBar.push_back(new HackingBar);
		hackingBar.back()->Init(speed, Vector3(currentX, bottomLeftPos.y - 120, 0), Vector3(currentX, topRightPos.y - 120, 0));

		currentX += distanceBetween;
		speed += 200;
	}
}

void HackingGame::Update(double dt)
{
	for(int i = 0; i < hackingBar.size(); ++i)
	{
		if(hackingBar[i]->topPos.y < topRightPos.y)
		{
			hackingBar[i]->goingUp = true;
		}
		else if(hackingBar[i]->bottomPos.y > bottomLeftPos.y)
		{
			hackingBar[i]->goingUp = false;
		}
		
		hackingBar[i]->Update(dt);
		
		if(hackingBar[i]->topPos.y > topRightPos.y + 120)
		{
			hackingBar[i]->vel.SetZero();
			hackingBar[i]->topPos.y = topRightPos.y + 120;
			hackingBar[i]->bottomPos.y = bottomLeftPos.y + 120;
		}
		else if(hackingBar[i]->bottomPos.y < bottomLeftPos.y - 120)
		{
			hackingBar[i]->vel.SetZero();
			hackingBar[i]->topPos.y = topRightPos.y - 120;
			hackingBar[i]->bottomPos.y = bottomLeftPos.y - 120;
		}
	}
}
bool HackingGame::Input()
{
	if(hackingBar[currentBar]->bottomPos.y + 10 >= bottomLeftPos.y  
		&& hackingBar[currentBar]->topPos.y - 10 <= topRightPos.y)
	{
		hackingBar[currentBar]->active = false;
		hackingBar[currentBar]->bottomPos.y = bottomLeftPos.y;
		hackingBar[currentBar]->topPos.y = topRightPos.y;
		currentBar++;
		return true;
	}
	else
	{
		if(currentBar > 0)
		{
			--currentBar;
			hackingBar[currentBar]->active = true;
		}
		return false;
	}
}