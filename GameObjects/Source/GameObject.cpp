#include "GameObject.h"
GameObject::GameObject()
{
}

GameObject::GameObject(int type, Vector3 pos)
{
	this->type = type;
	this->pos = pos;
	currentFrame = 0;
}

GameObject::~GameObject()
{
}