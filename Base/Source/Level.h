#ifndef LEVEL_H
#define LEVEL_H

#include "Map.h"
#include "LevelMap_Nodes.h"
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

	// Enemies
	CLevelMap_Nodes* LevelMap_Nodes;

	Mesh* background;

	CPosNode* HeroStartPosNode;

	bool sideView;
};

#endif