#include "GameObject.h"

GameObject::GameObject(int type, Vector3 pos)
{
	this->type = type;
	this->pos = pos;
	active = true;
}

GameObject::~GameObject()
{
}