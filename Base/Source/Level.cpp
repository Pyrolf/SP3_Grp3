#include "Level.h"

Level::Level()
	: m_cMap(NULL)
	, m_cRearMap(NULL)
	, AI_Manager(NULL)
	, background(NULL)
	, sideView(false)
{
}

Level::~Level()
{
	if(AI_Manager)
	{
		delete AI_Manager;
		AI_Manager = NULL;
	}

	if (gameObjectsManager)
	{
		delete gameObjectsManager;
		gameObjectsManager = NULL;
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