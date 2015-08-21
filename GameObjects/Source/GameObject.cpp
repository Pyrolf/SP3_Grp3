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

bool GameObject::CheckColision(Vector3 pos, int tileSize)
{
	Vector3 min(pos.x + 1, pos.y + 1, 0);
	Vector3 max(pos.x + tileSize - 1, pos.y + tileSize - 1, 0);

	if((min.x > this->pos.x && min.x < this->pos.x + tileSize) && (min.y > this->pos.y && min.y < this->pos.y + tileSize) || 
		(min.x > this->pos.x && min.x < this->pos.x + tileSize) && (max.y > this->pos.y && max.y < this->pos.y + tileSize) ||
		(max.x > this->pos.x && max.x < this->pos.x + tileSize) && (min.y > this->pos.y && min.y < this->pos.y + tileSize) ||
		(max.x > this->pos.x && max.x < this->pos.x + tileSize) && (max.y > this->pos.y && max.y < this->pos.y + tileSize))
	{
		return true;
	}

	return false;
}