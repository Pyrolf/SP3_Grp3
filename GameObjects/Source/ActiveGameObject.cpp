#include "ActiveGameObject.h"


ActiveGameObject::ActiveGameObject()
{
}

ActiveGameObject::ActiveGameObject(int type, Vector3 pos)
{
	id = -1;
	this->type = type;
	this->pos = pos;
	currentFrame = 0;

	active = false;
	canActivate = true;

	frameTime = currentFrameTime = 0;

	InitRanodmVars();
}

void ActiveGameObject::InitRanodmVars()
{
	switch(type)
	{
	case WET_FLOOR:
	{
		frameTime = 0.1;
		break;
	}
	case TIMING_DOOR:
		{
			frameTime = Math::RandFloatMinMax(3,6);
			currentFrameTime = 0;
			currentFrame = 1;
			break;
		}
	case BLOCK:
		{
			active = true;
			break;
		}
	case HEALTH_PACK:
		{
			active = true;
			break;
		}
	case TRAP:
		{
			frameTime = 0.015;
			break;
		}
	}
}

ActiveGameObject::~ActiveGameObject(void)
{
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
			currentFrameTime += dt;
			if(currentFrameTime > frameTime)
			{
				currentFrameTime = 0;
				if(active)
				{
					currentFrame = 1;
					active = false;
				}
				else
				{
					currentFrame = 0;
					active = true;
				}
			}
			break;
		}
	case TRAP:
		{
			if(active)
			{
				currentFrameTime += dt;
				if(currentFrameTime >= frameTime)
				{
					currentFrame += 1;
					currentFrameTime = 0;
				}
				if(currentFrame >= 4)
				{
					currentFrame = 4;
				}
			}
			else
			{
				currentFrame = 0;
			}
			break;
		}
	}
}

void ActiveGameObject::Reset()
{
	currentFrame = 0;

	active = false;
	canActivate = true;

	frameTime = currentFrameTime = 0;

	InitRanodmVars();
}