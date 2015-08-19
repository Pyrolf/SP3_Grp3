#include "Enemy.h"
#include <iostream>

CEnemy::CEnemy(void)
	: enemyAnimationDirection(DOWN)
	, enemyAnimationInvert(false)
	, enemyAnimationCounter(0.f)
	, hitHero(false)
	, maxRangeToDetect(0)
	, currentMode(RETURN)
	, idleTime(0)
	, justAlerted(false)
	, timeAlerted(0)
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
	if(DistFromHeroToEnemy <= maxRangeToDetect)
	{
		if(DistFromHeroToEnemy >= goManager->tileSize)
		{
			if(currentMode != CHASE)
			{
				currentMode = CHASE;
				justAlerted = true;
				timeAlerted = 1.f;
			}
		}
		else
		{
			if(currentMode != ATTACK)
			{
				currentMode = ATTACK;
				hitHero = true;
			}
		}
	}
	else
	{
		if(currentMode != RETURN && currentMode != PATROL && currentMode != IDLE)
		{
			currentMode = RETURN;
			justAlerted = false;
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
	case ATTACK:
		{
			theENEMYPosition.x += theENEMYPosition.x - heroPos.x;
			theENEMYPosition.y += theENEMYPosition.y - heroPos.y;
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
						int temp = rand() % 3;
						float x;
						if(temp == 0)
						{
							x = goManager->tileSize;
						}
						else if(temp == 1)
						{
							x = -goManager->tileSize;
						}
						else
						{
							x = 0;
						}
						temp = rand() % 3;
						float y;
						if(temp == 0)
						{
							y = goManager->tileSize;
						}
						else if(temp == 1)
						{
							y = -goManager->tileSize;
						}
						else
						{
							y = 0;
						}
						patrolTarget = Vector3(theENEMYPosition.x + x, theENEMYPosition.y + y);
						if(!CheckCollision(goManager, patrolTarget) && patrolTarget != theENEMYPosition)
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
						
						int temp = rand() % 3;
						float x;
						if(temp == 0)
						{
							x = goManager->tileSize;
						}
						else if(temp == 1)
						{
							x = -goManager->tileSize;
						}
						else
						{
							x = 0;
						}
						temp = rand() % 3;
						float y;
						if(temp == 0)
						{
							y = goManager->tileSize;
						}
						else if(temp == 1)
						{
							y = -goManager->tileSize;
						}
						else
						{
							y = 0;
						}
						patrolTarget = Vector3(theENEMYPosition.x + x, theENEMYPosition.y + y);
						if(!CheckCollision(goManager, patrolTarget) && patrolTarget != theENEMYPosition)
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
						
						int temp = rand() % 3;
						float x;
						if(temp == 0)
						{
							x = goManager->tileSize;
						}
						else if(temp == 1)
						{
							x = -goManager->tileSize;
						}
						else
						{
							x = 0;
						}
						temp = rand() % 3;
						float y;
						if(temp == 0)
						{
							y = goManager->tileSize;
						}
						else if(temp == 1)
						{
							y = -goManager->tileSize;
						}
						else
						{
							y = 0;
						}
						patrolTarget = Vector3(theENEMYPosition.x + x, theENEMYPosition.y + y);
						if(!CheckCollision(goManager, patrolTarget) && patrolTarget != theENEMYPosition)
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
	UpdateAnimation(theENEMYPosition, theENEMYPrevPosition, timeDiff);
	if(justAlerted)
	{
		if(timeAlerted > 0)
		{
			timeAlerted -= timeDiff;
		}
		else
		{
			justAlerted = false;
		}
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

void CEnemy::SetHitHero(bool hitHero)
{
	this->hitHero = hitHero;
}

bool CEnemy::GetHitHero(void)
{
	return hitHero;
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

void CEnemy::UpdateAnimation(Vector3 CurrentPos, Vector3 PrevPos, float timeDiff)
{
	if(CurrentPos.y > PrevPos.y)
	{
		enemyAnimationDirection = UP;
		enemyAnimationInvert = false;
		enemyAnimationCounter += 30 * timeDiff;
		if(enemyAnimationCounter > 3.0f)
			enemyAnimationCounter = 0.0f;
	}
	else if(CurrentPos.y < PrevPos.y)
	{
		enemyAnimationDirection = DOWN;
		enemyAnimationInvert = false;
		enemyAnimationCounter += 30 * timeDiff;
		if(enemyAnimationCounter > 3.0f)
			enemyAnimationCounter = 0.0f;
	}
	else if(CurrentPos.x < PrevPos.x)
	{
		enemyAnimationDirection = LEFT;
		enemyAnimationInvert = true;
		enemyAnimationCounter -= 30 * timeDiff;
		if(enemyAnimationCounter < 0.0f)
			enemyAnimationCounter = 3.0f;
	}
	else if(CurrentPos.x > PrevPos.x)
	{
		enemyAnimationDirection = RIGHT;
		enemyAnimationInvert = false;
		enemyAnimationCounter += 30 * timeDiff;
		if(enemyAnimationCounter > 3.0f)
			enemyAnimationCounter = 0.0f;
	}
}

CEnemy::ANIMATION_DIRECTION CEnemy::GetAnimationDirection(void)
{
	return enemyAnimationDirection;
}

void CEnemy::SetJustAlerted(bool justAlerted)
{
	this->justAlerted = justAlerted;
}

bool CEnemy::GetJustAlerted(void)
{
	return justAlerted;
}