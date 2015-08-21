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
					// Delete one col
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