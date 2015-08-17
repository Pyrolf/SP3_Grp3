#include "Enemy.h"
#include <iostream>

CEnemy::CEnemy(void)
	: theStrategy(NULL)
	, enemyAnimationInvert(false)
	, enemyAnimationCounter(0.f)
	, currentStrategy(NIL)
	, killedHero(false)
{
}

CEnemy::~CEnemy(void)
{
	if (theStrategy != NULL)
	{
		delete theStrategy;
		theStrategy = NULL;
	}
}

// Initialise this class instance
void CEnemy::Init(void)
{
	theENEMYPosition.x = 0;
	theENEMYPosition.y = 0;
	theENEMYInitialPosition.x = 0;
	theENEMYInitialPosition.y = 0;
	theENEMYFinalPosition.x = 0;
	theENEMYFinalPosition.y = 0;
	theDestination.x = 0;
	theDestination.y = 0;
}

// Set position x of the player
void CEnemy::SetPos_x(int pos_x, bool intial, float endPoint_x)
{
	theENEMYPosition.x = pos_x;
	if(intial)
	{
		theENEMYInitialPosition.x = pos_x;
		theENEMYFinalPosition.x = endPoint_x;
	}
}

// Set position y of the player
void CEnemy::SetPos_y(int pos_y, bool intial, float endPoint_y)
{
	theENEMYPosition.y = pos_y;
	if(intial)
	{
		theENEMYInitialPosition.y = pos_y;
		theENEMYFinalPosition.y = endPoint_y;
	}
}

// Set the destination of this enemy
void CEnemy::SetDestination(const int pos_x, const int pos_y)
{
	theDestination.x = pos_x;
	theDestination.y = pos_y;
	if(theStrategy != NULL)
	{
		theStrategy->SetDestination(theDestination.x, theDestination.y);
	}
}

// Get position x of the player
int CEnemy::GetPos_x(void)
{
	return theENEMYPosition.x;
}

// Get position y of the player
int CEnemy::GetPos_y(void)
{
	return theENEMYPosition.y;
}

// Set the destination of this enemy
int CEnemy::GetDestination_x(void)
{
	return theDestination.x;
}

// Set the destination of this enemy
int CEnemy::GetDestination_y(void)
{
	return theDestination.y;
}

// Set Animation Invert status of the player
void CEnemy::SetAnimationInvert(bool enemyAnimationInvert)
{
	this->enemyAnimationInvert = enemyAnimationInvert;
}

// Get Animation Invert status of the player
bool CEnemy::GetAnimationInvert(void)
{
	return enemyAnimationInvert;
}

// Set Animation Counter of the player
void CEnemy::SetAnimationCounter(float enemyAnimationCounter)
{
	this->enemyAnimationCounter = enemyAnimationCounter;
}

// Get Animation Counter of the player
float CEnemy::GetAnimationCounter(void)
{
	return enemyAnimationCounter;
}

/********************************************************************************
Hero Update
********************************************************************************/
void CEnemy::Update(CMap* m_cMap, float timeDiff)
{
	if (theStrategy != NULL)
	{
		if(theStrategy->Update( m_cMap, timeDiff))
		{
			killedHero = true;
		}
		theStrategy->GetEnemyPosition( (theENEMYPosition.x),
			(theENEMYPosition.y) );
	}
}

/********************************************************************************
Strategy
********************************************************************************/
void CEnemy::ChangeStrategy(CStrategy* theNewStrategy, bool bDelete)
{
	if (bDelete == true)
	{
		if (theStrategy != NULL)
		{
			delete theStrategy;
			theStrategy = NULL;
		}
	}
	theStrategy = theNewStrategy;
	if (theStrategy != NULL)
	{
		theStrategy->SetDestination( theDestination.x, theDestination.y );
		theStrategy->SetEnemyPosition(theENEMYPosition.x,
			theENEMYPosition.y);
	}
}

CEnemy::CURRENT_STRATEGY CEnemy::GetCurrentStrategy(void)
{
	return currentStrategy;
}

void CEnemy::SetCurrentStrategy(CEnemy::CURRENT_STRATEGY currentStrategy)
{
	this->currentStrategy = currentStrategy;
}

float CEnemy::GetInitialPos_x(void)
{
	return theENEMYInitialPosition.x;
}

float CEnemy::GetInitialPos_y(void)
{
	return theENEMYInitialPosition.y;
}

float CEnemy::GetFinalPos_x(void)
{
	return theENEMYFinalPosition.x;
}

float CEnemy::GetFinalPos_y(void)
{
	return theENEMYFinalPosition.y;
}

void CEnemy::SetKilledHero(bool killedHero)
{
	this->killedHero = killedHero;
}

bool CEnemy::GetKilledHero(void)
{
	return killedHero;
}