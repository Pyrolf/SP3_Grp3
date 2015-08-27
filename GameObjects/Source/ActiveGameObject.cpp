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

	frameTime = currentFrameTime = timmer = 0;

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
	case LOCKED_DOOR:
		{
			currentFrame = 1;
			break;
		}
	case HEALTH_PACK:
		{
			active = true;
			break;
		}
	case FIRE:
		{
			frameTime = 0.1;
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
	case LOCKED_DOOR:
		{
			if(active)
				{
					currentFrame = 0;
				}
			else
				{
					currentFrame = 1;
				}
			break;
		}
	case FIRE:
		{
			if(active)
			{
				timmer += dt;
				if(timmer > 1)
				{
					timmer = 0;
					active = false;
				}

				currentFrameTime += dt;
				if(currentFrameTime >= frameTime)
				{
					currentFrame += 1;
					currentFrameTime = 0;
				}
				if(currentFrame >= 5)
				{
					currentFrame = 1;
				}
			}
			else
			{
				timmer += dt;
				if(timmer > 1)
				{
					timmer = 0;
					active = true;
				}
				currentFrame = 0;
			}
			break;
		}
	}
}