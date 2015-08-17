#include "Level.h"

Level::Level()
	: m_cMap(NULL)
	, m_cRearMap(NULL)
	, theEnemy(NULL)
	, theGoodiesList(NULL)
	, background(NULL)
	, sideView(false)
{
}

Level::~Level()
{
	for(int i = 0; i < theEnemy.size(); i++)
	{
		if(theEnemy[i])
		{
			delete theEnemy[i];
			theEnemy[i] = NULL;
		}
	}
	for(int i = 0; i < theGoodiesList.size(); i++)
	{
		if(theGoodiesList[i])
		{
			delete theGoodiesList[i];
			theGoodiesList[i] = NULL;
		}
	}

	if (m_cMap)
	{
		delete m_cMap;
		m_cMap = NULL;
	}
	if(m_cRearMap)
	{
		delete m_cRearMap;
		m_cRearMap = NULL;
	}
}