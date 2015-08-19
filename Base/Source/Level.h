#ifndef LEVEL_H
#define LEVEL_H

#include "Map.h"
#include "AIManager.h"
#include "Vector2.h"
#include "Goodies.h"

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
	GameObjectFactory* gameObjectsManager;

	// Enemies
	CAIManager* AI_Manager;

	Mesh* background;

	Vector2 HeroStartPos;

	bool sideView;
};

#endif