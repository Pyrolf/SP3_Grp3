#include "LevelMap_Nodes.h"


CLevelMap_Nodes::CLevelMap_Nodes(void)
{
	topLeft = topRight = bottomLeft = bottomRight = current = prev = NULL;
}


CLevelMap_Nodes::~CLevelMap_Nodes(void)
{
	if(topLeft != NULL)
	{
		if(topLeft != bottomRight)
		{
			current = topLeft;
			// Delete all rows
			for(int currentRow = 0; current != NULL; ++currentRow)
			{
				current = topLeft;
				if(topLeft->down != NULL)
				{
					// Move topLeft down
					topLeft = topLeft->down;
				}
				else
				{
					topLeft = NULL;
				}
				// Delete one row
				for(int currentCol = 0; current != NULL; ++currentCol)
				{
					// Delete one column
					prev = current;
					current = current->right;
					delete prev;
				}
			}
		}
		else
		{
			delete topLeft;
			topLeft = NULL;
		}
		// Point all pointers to NULL
		topRight = NULL;
		bottomLeft = NULL;
		bottomRight = NULL;
		current = NULL;
		prev = NULL;
	}
}

void CLevelMap_Nodes::GenerateNodes(CMap* map, CAIManager* ai_manager, GameObjectFactory* go_manager)
{
	int ai_index = 0;
	int go_index = 0;
	current = NULL;
	for(int i = 1; i < map->getNumOfTiles_MapHeight(); i ++)
	{
		prev = NULL;
		for(int k = 0; k < map->getNumOfTiles_MapWidth(); k ++)
		{
			current = new CPosNode(Vector3(k * map->GetTileSize(), (map->getNumOfTiles_MapHeight() - i - 1) * map->GetTileSize(), 0), map->theScreenMap[i][k]);
			if(i == 1)
			{
				if(k == 0)
				{
					// Point topLeft to current
					topLeft = current;
					// Point bottomLeft to current
					bottomLeft = current;
				}
				else if(k == map->getNumOfTiles_MapWidth() - 1)
				{
					// Point topRight to current
					topRight = current;
					// Point right
					prev->right = current;
					// Point left
					current->left = prev;
					// Point bottomRight to current
					bottomRight = current;
				}
				else
				{
					// Point right
					prev->right = current;
					// Point left
					current->left = prev;
				}
			}
			else
			{
				if(k == 0)
				{
					// Point up
					current->up = bottomLeft;
					// Point down
					bottomLeft->down = current;
					// Point bottomLeft to current
					bottomLeft = current;
				}
				else if(k == map->getNumOfTiles_MapWidth() - 1)
				{
					// Point up
					current->up = bottomRight;
					// Point down
					bottomRight->down = current;
					// Point right
					prev->right = current;
					// Point left
					current->left = prev;
					// Point bottomRight to current
					bottomRight = current;
				}
				else
				{
					// Point up
					current->up = prev->up->right;
					// Point down
					prev->up->right->down = current;
					// Point right
					prev->right = current;
					// Point left
					current->left = prev;
				}
			}
			prev = current;
			if(prev->posType > CPosNode::NONE
				&& prev->posType != CPosNode::TOTAL_NON_ACTIVE_GO
				&& prev->posType < CPosNode::TOTAL_ACTIVE_GO)
			{
				prev->gameObject = go_manager->GoList[go_index];
				++go_index;
			}
			else if(prev->posType == CPosNode::ENEMY_INITIAL_POS)
			{
				ai_manager->enemiesList[ai_index]->SetInitialPosNode(prev);
				ai_manager->enemiesList[ai_index]->SetPos(prev->pos);
				ai_manager->enemiesList[ai_index]->SetCurrentPosNode(prev);
				ai_manager->enemiesList[ai_index]->SetTargetPosNode(prev);
				++ai_index;
			}
		}
	}
}

CPosNode* CLevelMap_Nodes::FindHeroInitialNode(void)
{
	current = prev = topLeft;
	for(int currentRow = 0; current != NULL; ++currentRow)
	{
		// Move one row
		for(int currentCol = 0; current != NULL; ++currentCol)
		{
			if(current->posType == CPosNode::HERO_INIT_POS)
			{
				return current;
			}
			// Move one column
			current = current->right;
		}
		current = prev->down;
		prev = prev->down;
	}
	return NULL;
}