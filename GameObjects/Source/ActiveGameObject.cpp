#include "ActiveGameObject.h"


ActiveGameObject::ActiveGameObject()
{
}

ActiveGameObject::ActiveGameObject(int type, Vector3 pos)
{
	GameObject::GameObject(type, pos);
}

ActiveGameObject::~ActiveGameObject(void)
{
}