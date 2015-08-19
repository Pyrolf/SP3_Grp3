#include "ActiveGameObject.h"


ActiveGameObject::ActiveGameObject()
{
}

ActiveGameObject::ActiveGameObject(int type, Vector3 pos)
{
	GameObject::GameObject(type, pos);
	active = false;
	currentFrame = 0;
	random = 0;
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
			break;
		}
	case TIMING_DOOR:
		{
			break;
		}
	}
}