#ifndef LEVEL_H
#define LEVEL_H

#include "Map.h"
#include "Enemy.h"
#include "Vector2.h"
#include "Goodies.h"
#include "GameObjectFactory.h"

struct Level
{
public:
	Level();
	~Level();

	// Handle to the tilemaps
	CMap* m_cMap;

	// Codes for Parallax Scrolling
	CMap* m_cRearMap;
	
	// GameObj vector
	GameObjectFactory* gameObjects;

	// Enemies
	vector<CEnemy*> theEnemy;

	vector<CGoodies*> theGoodiesList;

	Mesh* background;

	Vector2 HeroStartPos;

	bool sideView;
};

#endif