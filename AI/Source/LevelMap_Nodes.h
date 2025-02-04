#pragma once
#include <iostream>
#include "AIManager.h"

using namespace std;

class CLevelMap_Nodes
{
private:
		CPosNode *topLeft, *topRight, *bottomLeft, *bottomRight, *current, *prev;
public:
	CLevelMap_Nodes(void);
	~CLevelMap_Nodes(void);

	void GenerateNodes(CMap* map, CAIManager* ai_manager, GameObjectFactory* go_manager);
	CPosNode* FindHeroInitialNode(void);
};

