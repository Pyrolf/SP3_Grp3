#include "Enemy.h"
#include <iostream>

CEnemy::CEnemy(void)
	: enemyAnimationInvert(false)
	, enemyAnimationCounter(0.f)
	, killedHero(false)
	, maxRangeToDetect(0)
	, currentMode(RETURN)
	, idleTime(0)
{
}

CEnemy::~CEnemy(void)
{
}

// Initialise this class instance
void CEnemy::Init(void)
{
	theENEMYPosition.x = 0;
	theENEMYPosition.y = 0;
	theENEMYInitialPosition.x = 0;
	theENEMYInitialPosition.y = 0;
}

// Set position x of the player
void CEnemy::SetPos_x(int pos_x, bool intial, float endPoint_x)
{
	theENEMYPosition.x = pos_x;
	if(intial)
	{
		theENEMYInitialPosition.x = pos_x;
	}
}

// Set position y of the player
void CEnemy::SetPos_y(int pos_y, bool intial, float endPoint_y)
{
	theENEMYPosition.y = pos_y;
	if(intial)
	{
		theENEMYInitialPosition.y = pos_y;
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
void CEnemy::Update(GameObjectFactory* goManager, float timeDiff, Vector3 heroPos)
{
	float DistFromHeroToEnemy = (theENEMYPosition - heroPos).Length();
	if(DistFromHeroToEnemy < maxRangeToDetect)
	{
		if(DistFromHeroToEnemy > goManager->tileSize)
		{
			if(currentMode != CHASE)
			{
				currentMode = CHASE;
			}
		}
		else
		{
			if(currentMode != ATTACK)
			{
				currentMode = ATTACK;
				killedHero = true;
			}
		}
	}
	else
	{
		if(currentMode != RETURN && currentMode != PATROL && currentMode != IDLE)
		{
			currentMode = RETURN;
		}
	}

	Vector3 theENEMYPrevPosition = theENEMYPosition;
	switch(currentMode)
	{
	case CHASE:
		{
			MoveEnemy(goManager, timeDiff, heroPos);
		}
		break;
	case RETURN:
		{
			MoveEnemy(goManager, timeDiff, theENEMYInitialPosition);
			if(theENEMYPosition == theENEMYInitialPosition|| theENEMYPosition == theENEMYPrevPosition)
			{
				if(rand() % 2 == 0)
				{
					currentMode = PATROL;
					while(true)
					{
						patrolTarget = Vector3(Math::RandFloatMinMax(theENEMYInitialPosition.x - maxRangeToDetect, theENEMYInitialPosition.x + maxRangeToDetect), Math::RandFloatMinMax(theENEMYInitialPosition.y - maxRangeToDetect, theENEMYInitialPosition.y + maxRangeToDetect));
						if(!CheckCollision(goManager, patrolTarget))
							break;
					}
				}
				else
				{
					currentMode = IDLE;
					idleTime = Math::RandFloatMinMax(1, 3);
				}
			}
		}
		break;
	case PATROL:
		{
			MoveEnemy(goManager, timeDiff, patrolTarget);
			if(theENEMYPosition == patrolTarget || theENEMYPosition == theENEMYPrevPosition)
			{
				if(rand() % 2 == 0)
				{
					while(true)
					{
						patrolTarget = Vector3(Math::RandFloatMinMax(theENEMYInitialPosition.x - maxRangeToDetect, theENEMYInitialPosition.x + maxRangeToDetect), Math::RandFloatMinMax(theENEMYInitialPosition.y - maxRangeToDetect, theENEMYInitialPosition.y + maxRangeToDetect));
						if(!CheckCollision(goManager, patrolTarget))
							break;
					}
				}
				else
				{
					currentMode = IDLE;
					idleTime = Math::RandFloatMinMax(1, 3);
				}
			}
		}
		break;
	case IDLE:
		{
			idleTime -=timeDiff;
			if(idleTime <= 0.f)
			{
				if(rand() % 2 == 0)
				{
					currentMode = PATROL;
					while(true)
					{
						patrolTarget = Vector3(Math::RandFloatMinMax(theENEMYInitialPosition.x - maxRangeToDetect, theENEMYInitialPosition.x + maxRangeToDetect), Math::RandFloatMinMax(theENEMYInitialPosition.y - maxRangeToDetect, theENEMYInitialPosition.y + maxRangeToDetect));
						if(!CheckCollision(goManager, patrolTarget))
							break;
					}
				}
				else
				{
					idleTime = Math::RandFloatMinMax(1, 3);
				}
			}
		}
		break;
	}
}

void CEnemy::SetCurrentMode(CEnemy::CURRENT_MODE currentMode)
{
	this->currentMode = currentMode;
}

CEnemy::CURRENT_MODE CEnemy::GetCurrentMode(void)
{
	return currentMode;
}

float CEnemy::GetInitialPos_x(void)
{
	return theENEMYInitialPosition.x;
}

float CEnemy::GetInitialPos_y(void)
{
	return theENEMYInitialPosition.y;
}

void CEnemy::SetKilledHero(bool killedHero)
{
	this->killedHero = killedHero;
}

bool CEnemy::GetKilledHero(void)
{
	return killedHero;
}

void CEnemy::SetMaxRangeToDetect(int maxRangeToDetect)
{
	this->maxRangeToDetect = maxRangeToDetect;
}

int CEnemy::GetMaxRangeToDetect(void)
{
	return maxRangeToDetect;
}

bool CEnemy::CheckCollision(GameObjectFactory* goManager, Vector3 pos)
{
	GameObject* goCollidedWith = goManager->CheckColision(pos);
	if(goCollidedWith)
	{
		switch (goCollidedWith->type)
		{
		case GameObject::WALL:
			{
				return true;
			}
			break;
		case GameObject::DOOR:
			{
				return true;
			}
			break;
		default :
			{
				return false;
			}
			break;
		}
	}
	else
	{
		return false;
	}
}

void CEnemy::MoveEnemy(GameObjectFactory* goManager, float timeDiff, Vector3 target)
{
	Vector3 theENEMYPrevPosition = theENEMYPosition;

	Vector3 diffInDis_x = Vector3(target.x) - Vector3(theENEMYPosition.x);
	Vector3 diffInDis_y = Vector3(0, target.y) - Vector3(0, theENEMYPosition.y);

	if(diffInDis_x.Length() < diffInDis_y.Length())
	{
		if(theENEMYPosition.x != target.x)
		{
			float moveBy = ((diffInDis_x).Normalized()).x * 100 * timeDiff;
			if(!CheckCollision(goManager, theENEMYPosition + Vector3(moveBy)))
			{
				theENEMYPosition.x += moveBy;
				if((theENEMYPrevPosition.x < target.x && theENEMYPosition.x >= target.x)
					|| (theENEMYPrevPosition.x > target.x && theENEMYPosition.x <= target.x))
				{
					theENEMYPosition.x = target.x;
				}
			}
			else
			{
				if(theENEMYPosition.y != target.y)
				{
					float moveBy = ((diffInDis_y).Normalized()).y * 100 * timeDiff;
					if(!CheckCollision(goManager, theENEMYPosition + Vector3(0, moveBy)))
					{
						theENEMYPosition.y += moveBy;
						if((theENEMYPrevPosition.y < target.y && theENEMYPosition.y >= target.y)
							|| (theENEMYPrevPosition.y > target.y && theENEMYPosition.y <= target.y))
						{
							theENEMYPosition.y = target.y;
						}
					}
				}
			}
		}
		else if(theENEMYPosition.y != target.y)
		{
			float moveBy = ((diffInDis_y).Normalized()).y * 100 * timeDiff;
			if(!CheckCollision(goManager, theENEMYPosition + Vector3(0, moveBy)))
			{
				theENEMYPosition.y += moveBy;
				if((theENEMYPrevPosition.y < target.y && theENEMYPosition.y >= target.y)
					|| (theENEMYPrevPosition.y > target.y && theENEMYPosition.y <= target.y))
				{
					theENEMYPosition.y = target.y;
				}
			}
		}
	}
	else
	{
		if(theENEMYPosition.y != target.y)
		{
			float moveBy = ((diffInDis_y).Normalized()).y * 100 * timeDiff;
			if(!CheckCollision(goManager, theENEMYPosition + Vector3(0, moveBy)))
			{
				theENEMYPosition.y += moveBy;
				if((theENEMYPrevPosition.y < target.y && theENEMYPosition.y >= target.y)
					|| (theENEMYPrevPosition.y > target.y && theENEMYPosition.y <= target.y))
				{
					theENEMYPosition.y = target.y;
				}
			}
			else
			{
				if(theENEMYPosition.x != target.x)
				{
					float moveBy = ((diffInDis_x).Normalized()).x * 100 * timeDiff;
					if(!CheckCollision(goManager, theENEMYPosition + Vector3(moveBy)))
					{
						theENEMYPosition.x += moveBy;
						if((theENEMYPrevPosition.x < target.x && theENEMYPosition.x >= target.x)
							|| (theENEMYPrevPosition.x > target.x && theENEMYPosition.x <= target.x))
						{
							theENEMYPosition.x = target.x;
						}
					}
				}
			}
		}
		else if(theENEMYPosition.x != target.x)
		{
			float moveBy = ((diffInDis_x).Normalized()).x * 100 * timeDiff;
			if(!CheckCollision(goManager, theENEMYPosition + Vector3(moveBy)))
			{
				theENEMYPosition.x += moveBy;
				if((theENEMYPrevPosition.x < target.x && theENEMYPosition.x >= target.x)
					|| (theENEMYPrevPosition.x > target.x && theENEMYPosition.x <= target.x))
				{
					theENEMYPosition.x = target.x;
				}
			}
		}
	}
}