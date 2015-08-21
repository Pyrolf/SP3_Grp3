#include "ActiveGameObject.h"


ActiveGameObject::ActiveGameObject()
{
}

ActiveGameObject::ActiveGameObject(int type, Vector3 pos)
{
	this->type = type;
	this->pos = pos;
	currentFrame = 0;

	active = false;
	canActivate = true;

	randomInt = NULL;
	randomFloat = NULL;

	InitRanodmVars();
}

void ActiveGameObject::InitRanodmVars()
{
	switch(type)
	{
	case WET_FLOOR:
	{
		frameTime = 0.15;
		currentFrameTime = 0; 
		break;
	}
	case TIMING_DOOR:
		{
			randomInt = new int;
			randomFloat = new float;
			
			*randomInt = Math::RandIntMinMax(3,6);
			*randomFloat = 0;
			break;
		}
	case HEALTH_PACK:
		{
			active = true;
			break;
		}
	}
}

ActiveGameObject::~ActiveGameObject(void)
{
	if(randomInt)
	{
		delete randomInt;
		randomInt = NULL;
	}
	if(randomFloat)
	{
		delete randomFloat;
		randomFloat = NULL;
	}
}

void ActiveGameObject::update(double dt)
{
	switch(type)
	{
	case WET_FLOOR:
		{
			if(!canActivate)
			{
				active = false;
			}
			else if(active)
			{
				currentFrameTime += dt;
				if(currentFrameTime >= frameTime)
				{
					currentFrame += 1;
					currentFrameTime = 0;
				}
				if(currentFrame >= 3)
				{
					currentFrame = 0;
					active = false;
					canActivate = false;
				}
			}
			break;
		}
	case TIMING_DOOR:
		{
			*randomFloat += dt;
			if(*randomFloat > *randomInt)
			{
				*randomFloat = 0;
				if(active)
				{
					currentFrame = 0;
					active = false;
				}
				else
				{
					currentFrame = 1;
					active = true;
				}
			}
			break;
		}
	case LOCKED_DOOR:
		{
			if(active)
				{
					currentFrame = 0;
					active = false;
				}
				else
				{
					currentFrame = 1;
					active = true;
				}
			break;
		}
	}
}