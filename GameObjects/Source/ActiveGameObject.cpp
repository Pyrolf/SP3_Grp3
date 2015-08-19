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
				currentFrame += dt;
				//if(currentFrame >= numofsprite)
				//{
				//		currentFrame = 0;
				//		active = false;
				//}
			}
			break;
		}
	case TIMING_DOOR:
		{

			break;
		}
	}
}