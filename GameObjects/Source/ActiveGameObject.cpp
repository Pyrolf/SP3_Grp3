#include "ActiveGameObject.h"


ActiveGameObject::ActiveGameObject()
{
}

ActiveGameObject::ActiveGameObject(int type, Vector3 pos)
{
	GameObject::GameObject(type, pos);
	active = false;
	
	randomInt = NULL;
	randomFloat = NULL;

	InitRanodmVars();
}

void ActiveGameObject::InitRanodmVars()
{
	switch(type)
	{
	case TIMING_DOOR:
		{
			randomInt = new int;
			randomFloat = new float;
			
			*randomInt = Math::RandIntMinMax(3,6);
			*randomFloat = 0;
			break;
		}
	case HEALTH:
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
			if(active)
			{
				currentFrameTime += dt;
				//if(currentFrameTime >= FrameTime)
				//{
				//		currentFrame += 1;
				//		currentFrameTime = 0;
				//}
				//if(currentFrame > numofFrames)
				//{
				//	currentFrame = 0;
				//  active = false;
				//}
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