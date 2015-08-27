#include "Enemy.h"
#include <iostream>

CEnemy::CEnemy(void)
	: enemyAnimationDirection(DOWN)
	, enemyAnimationInvert(false)
	, enemyAnimationCounter(0.f)
	, hitHero(false)
	, maxRangeToDetect(0)
	, currentMode(IDLE)
	, time(0)
	, theENEMYPosition(Vector3(0,0,0))
	, theENEMYInitialPosNode(NULL)
	, theENEMYCurrentPosNode(NULL)
	, theENEMYTargetPosNode(NULL)
	, vel(Vector3(0,0,0))
	, movementSpeed(200.0f)
{
}

CEnemy::~CEnemy(void)
{
	if(theENEMYInitialPosNode)
	{
		theENEMYInitialPosNode = NULL;
	}
	if(theENEMYCurrentPosNode)
	{
		theENEMYCurrentPosNode = NULL;
	}
	if(theENEMYTargetPosNode)
	{
		theENEMYTargetPosNode = NULL;
	}
}


void CEnemy::Reset(void)
{
	theENEMYPosition = theENEMYInitialPosNode->pos;
	theENEMYCurrentPosNode = theENEMYInitialPosNode;
	theENEMYTargetPosNode = theENEMYCurrentPosNode;

	currentMode = RETURN;

	enemyAnimationDirection = DOWN;
	enemyAnimationCounter = 0.0f;
	enemyAnimationInvert = false;
}


// Set position x of the enemy
void CEnemy::SetPos_x(float pos_x)
{
	theENEMYPosition.x = pos_x;
}

// Set position y of the enemy
void CEnemy::SetPos_y(float pos_y)
{
	theENEMYPosition.y = pos_y;
}

// Set position of the enemy
void CEnemy::SetPos(Vector3 pos)
{
	theENEMYPosition.x = pos.x;
	theENEMYPosition.y = pos.y;
}

// Set initial position node of the enemy
void CEnemy::SetInitialPosNode(CPosNode* posNode)
{
	this->theENEMYInitialPosNode = posNode;
}

// Set current position node of the enemy
void CEnemy::SetCurrentPosNode(CPosNode* posNode)
{
	this->theENEMYCurrentPosNode = posNode;
}

// Set target position node of the enemy
void CEnemy::SetTargetPosNode(CPosNode* posNode)
{
	this->theENEMYTargetPosNode = posNode;
}


// Get position of the player
Vector3 CEnemy::GetPos(void)
{
	return theENEMYPosition;
}

// Get current position node of the player
CPosNode* CEnemy::GetCurrentPosNode(void)
{
	return theENEMYCurrentPosNode;
}

// Get target position node of the player
CPosNode* CEnemy::GetTargetPosNode(void)
{
	return theENEMYTargetPosNode;
}

// Get velocity of the player
Vector3 CEnemy::GetVel(void)
{
	return vel;
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

// Set Animation Direction status of the enemy
void CEnemy::SetAnimationDirection(ANIMATION_DIRECTION dir)
{
	this->enemyAnimationDirection = dir;
}

CEnemy::ANIMATION_DIRECTION CEnemy::GetAnimationDirection(void)
{
	return enemyAnimationDirection;
}


void CEnemy::SetCurrentMode(CEnemy::CURRENT_MODE currentMode)
{
	this->currentMode = currentMode;
}

CEnemy::CURRENT_MODE CEnemy::GetCurrentMode(void)
{
	return currentMode;
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

// Set time of the enemy
void CEnemy::SetTime(float time)
{
	this->time = time;
}

// Get time of the enemy
float CEnemy::GetTime(void)
{
	return time;
}

// Check current mode
void CEnemy::CheckMode(CPosNode* heroPosNode, int tileSize, Vector3 heroPos)
{
	float DistFromHeroToEnemy = (theENEMYPosition - heroPos).Length();
	float DistFromHeroToEnemyInit = (heroPos - theENEMYInitialPosNode->pos).Length();
	// If within range of detection
	if(checkIfHeroIsWithinSight(heroPos) && DistFromHeroToEnemyInit <= maxRangeToDetect * 2)
	{
		// If not chase or attack
		if(currentMode != CHASE && currentMode != ATTACK)
		{
			// Mode = CHASE
			currentMode = CHASE;
			ChaseCheck(heroPosNode, tileSize);
		}
		// If chase
		else if(currentMode == CHASE)
		{
			// if path is empty or player moved
			if(enemyPath.size() == 0 || enemyPath[0] != heroPosNode)
			{
				// Find a path
				enemyPath = PathFinding(heroPosNode, tileSize);
				ChaseCheck(heroPosNode, tileSize);
			}
			else
			{
				theENEMYTargetPosNode = enemyPath.back();
				enemyPath.pop_back();
				CalculateVel();
			}
		}
	}
	else
	{
		// If not return/ patrol/ idle
		if(currentMode != RETURN && currentMode != PATROL && currentMode != IDLE)
		{
			ReturnCheck(tileSize);
		}
		// If return
		else if(currentMode == RETURN)
		{
			// if theENEMYCurrentPosNode not equal to theENEMYInitialPosNode
			if(theENEMYCurrentPosNode != theENEMYInitialPosNode)
			{
				theENEMYTargetPosNode = enemyPath.back();
				enemyPath.pop_back();
				CalculateVel();
				currentMode = RETURN;
			}
			// if theENEMYCurrentPosNode equal to theENEMYInitialPosNode
			else
			{
				ChoosePatrolOrIdleMode();
			}
		}
	}
}

void CEnemy::ChaseCheck(CPosNode* heroPosNode, int tileSize)
{
	// Find a path
	enemyPath = PathFinding(heroPosNode, tileSize);
	// if path not empty
	if(enemyPath.size() != 0)
	{
		// if theENEMYTargetPosNode is equal to next path node
		if(theENEMYTargetPosNode == enemyPath.back())
		{
			enemyPath.pop_back();
		}
		if(enemyPath.size() != 0)
		{
			theENEMYTargetPosNode = enemyPath.back();
			enemyPath.pop_back();
			CalculateVel();
		}
	}
	// if path is empty
	else
	{
		ReturnCheck(tileSize);
	}
}

void CEnemy::ReturnCheck(int tileSize)
{
	// if theENEMYCurrentPosNode is not theENEMYInitialPosNode
	if(theENEMYCurrentPosNode != theENEMYInitialPosNode)
	{
		// Mode = RETURN
		currentMode = RETURN;
		// Find a path
		enemyPath = PathFinding(theENEMYInitialPosNode, tileSize);
		// if path not empty
		if(enemyPath.size() != 0)
		{
			// if theENEMYTargetPosNode is equal to next path node
			if(theENEMYTargetPosNode == enemyPath.back())
			{
				enemyPath.pop_back();
			}
			if(enemyPath.size() != 0)
			{
				theENEMYTargetPosNode = enemyPath.back();
				enemyPath.pop_back();
				CalculateVel();
			}
		}
		else
		{
			// if path is empty
			ChoosePatrolOrIdleMode();
		}
	}
	// if theENEMYCurrentPosNode is theENEMYInitialPosNode
	else
	{
		ChoosePatrolOrIdleMode();
	}
}


bool CEnemy::checkIfHeroIsWithinSight(Vector3 heroPos)
{
	// if within radius
	if((theENEMYPosition - heroPos).Length() <= maxRangeToDetect)
	{
		// if enemy looking up and hero is on top
		if((enemyAnimationDirection == UP) && (heroPos.y >= theENEMYPosition.y)
			// if enemy looking down and hero is below
			||(enemyAnimationDirection == DOWN) && (heroPos.y <= theENEMYPosition.y)
			// if enemy looking left and hero is on the left
			||(enemyAnimationDirection == LEFT) && (heroPos.x <= theENEMYPosition.x)
			// if enemy looking right and hero is on the right
			||(enemyAnimationDirection == RIGHT) && (heroPos.x >= theENEMYPosition.x))
		{
			return true;
		}
	}

	// If not within sight
	return false;
}


// Choose patrol or idle mode
void CEnemy::ChoosePatrolOrIdleMode(void)
{
	if(rand() % 2 == 0)
	{
		currentMode = PATROL;
		while(true)
		{
			int temp = rand() % 4;
			if(temp == 0)
			{
				theENEMYTargetPosNode = theENEMYTargetPosNode->up;
			}
			else if(temp == 1)
			{
				theENEMYTargetPosNode = theENEMYTargetPosNode->down;
			}
			else if(temp == 2)
			{
				theENEMYTargetPosNode = theENEMYTargetPosNode->left;
			}
			else
			{
				theENEMYTargetPosNode = theENEMYTargetPosNode->right;
			}
			if(theENEMYTargetPosNode->posType == CPosNode::NONE
				|| theENEMYTargetPosNode->posType > CPosNode::TOTAL_ACTIVE_GO)
			{
				CalculateVel();
				break;
			}
			theENEMYTargetPosNode = theENEMYCurrentPosNode;
		}
	}
	else
	{
		currentMode = IDLE;
		time = Math::RandFloatMinMax(1, 2);
	}
}

void CEnemy::CalculateVel(void)
{
	if(theENEMYCurrentPosNode->up == theENEMYTargetPosNode)
	{
		vel.Set(0, movementSpeed, 0);
	}
	else if(theENEMYCurrentPosNode->down == theENEMYTargetPosNode)
	{
		vel.Set(0, -movementSpeed, 0);
	}
	else if(theENEMYCurrentPosNode->left == theENEMYTargetPosNode)
	{
		vel.Set(-movementSpeed, 0, 0);
	}
	else if(theENEMYCurrentPosNode->right == theENEMYTargetPosNode)
	{
		vel.Set(movementSpeed, 0, 0);
	}
}

/********************************************************************************
Hero Update
********************************************************************************/
void CEnemy::Update(int tileSize, float timeDiff, CPosNode* heroPosNode, Vector3 heroPos)
{
	Vector3 theENEMYPrevPosition = theENEMYPosition;
	switch(currentMode)
	{
	case CHASE:
		{
			moving(timeDiff);
			float DistFromHeroToEnemy = (theENEMYPosition - heroPos).Length();
			// If within range of attack
			if(DistFromHeroToEnemy <= tileSize * 0.5)
			{
				// If not attack
				if(currentMode != ATTACK)
				{
					currentMode = ATTACK;
					hitHero = true;
					time = 0.5f;
					enemyPath.push_back(theENEMYTargetPosNode);

					// If target at up side
					if(theENEMYCurrentPosNode->up == theENEMYTargetPosNode)
					{
						theENEMYTargetPosNode = theENEMYTargetPosNode->down;
						theENEMYCurrentPosNode = theENEMYCurrentPosNode->down;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
					}
					// If target at down side
					else if(theENEMYCurrentPosNode->down == theENEMYTargetPosNode)
					{
						theENEMYTargetPosNode = theENEMYTargetPosNode->up;
						theENEMYCurrentPosNode = theENEMYCurrentPosNode->up;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
					}
					// If target at left side
					else if(theENEMYCurrentPosNode->left == theENEMYTargetPosNode)
					{
						theENEMYTargetPosNode = theENEMYTargetPosNode->right;
						theENEMYCurrentPosNode = theENEMYCurrentPosNode->right;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
					}
					// If target at right side
					else if(theENEMYCurrentPosNode->right == theENEMYTargetPosNode)
					{
						theENEMYTargetPosNode = theENEMYTargetPosNode->left;
						theENEMYCurrentPosNode = theENEMYCurrentPosNode->left;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
					}

					while(theENEMYCurrentPosNode->posType > CPosNode::NONE 
						&& theENEMYCurrentPosNode->posType < CPosNode::ENEMY_INITIAL_POS)
					{
						theENEMYCurrentPosNode = theENEMYTargetPosNode;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
						if(enemyPath.size() != 0)
						{
							theENEMYTargetPosNode = enemyPath.back();
							enemyPath.pop_back();
						}
						else
						{
							theENEMYTargetPosNode = heroPosNode;
						}
					}

				}
			}
			else
			{
				if(currentMode == NIL)
				{
					currentMode = CHASE;
					CheckMode(heroPosNode, tileSize, heroPos);
				}
			}
		}
		break;
	case ATTACK:
		{
			time -=timeDiff;
			if(time <= 0.f)
			{
				currentMode = CHASE;
				CheckMode(heroPosNode, tileSize, heroPos);
			}
		}
		break;
	case RETURN:
		{
			moving(timeDiff);
			float DistFromHeroToEnemy = (theENEMYPosition - heroPos).Length();
			// If within range of attack
			if(DistFromHeroToEnemy <= tileSize * 0.5)
			{
				// If not attack
				if(currentMode != ATTACK)
				{
					currentMode = ATTACK;
					hitHero = true;
					time = 0.5f;
					enemyPath.push_back(theENEMYTargetPosNode);

					// If target at up side
					if(theENEMYCurrentPosNode->up == theENEMYTargetPosNode)
					{
						theENEMYTargetPosNode = theENEMYTargetPosNode->down;
						theENEMYCurrentPosNode = theENEMYCurrentPosNode->down;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
					}
					// If target at down side
					else if(theENEMYCurrentPosNode->down == theENEMYTargetPosNode)
					{
						theENEMYTargetPosNode = theENEMYTargetPosNode->up;
						theENEMYCurrentPosNode = theENEMYCurrentPosNode->up;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
					}
					// If target at left side
					else if(theENEMYCurrentPosNode->left == theENEMYTargetPosNode)
					{
						theENEMYTargetPosNode = theENEMYTargetPosNode->right;
						theENEMYCurrentPosNode = theENEMYCurrentPosNode->right;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
					}
					// If target at right side
					else if(theENEMYCurrentPosNode->right == theENEMYTargetPosNode)
					{
						theENEMYTargetPosNode = theENEMYTargetPosNode->left;
						theENEMYCurrentPosNode = theENEMYCurrentPosNode->left;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
					}

					while(theENEMYCurrentPosNode->posType > CPosNode::NONE 
						&& theENEMYCurrentPosNode->posType < CPosNode::ENEMY_INITIAL_POS)
					{
						theENEMYCurrentPosNode = theENEMYTargetPosNode;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
						if(enemyPath.size() != 0)
						{
							theENEMYTargetPosNode = enemyPath.back();
							enemyPath.pop_back();
						}
						else
						{
							theENEMYTargetPosNode = heroPosNode;
						}
					}

				}
			}
			else
			{
				if(currentMode == NIL)
				{
					currentMode = RETURN;
					CheckMode(heroPosNode, tileSize, heroPos);
				}
			}
		}
		break;
	case PATROL:
		{
			moving(timeDiff);
			float DistFromHeroToEnemy = (theENEMYPosition - heroPos).Length();
			// If within range of attack
			if(DistFromHeroToEnemy <= tileSize * 0.5)
			{
				// If not attack
				if(currentMode != ATTACK)
				{
					currentMode = ATTACK;
					hitHero = true;
					time = 0.5f;
					enemyPath.push_back(theENEMYTargetPosNode);

					// If target at up side
					if(theENEMYCurrentPosNode->up == theENEMYTargetPosNode)
					{
						theENEMYTargetPosNode = theENEMYTargetPosNode->down;
						theENEMYCurrentPosNode = theENEMYCurrentPosNode->down;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
					}
					// If target at down side
					else if(theENEMYCurrentPosNode->down == theENEMYTargetPosNode)
					{
						theENEMYTargetPosNode = theENEMYTargetPosNode->up;
						theENEMYCurrentPosNode = theENEMYCurrentPosNode->up;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
					}
					// If target at left side
					else if(theENEMYCurrentPosNode->left == theENEMYTargetPosNode)
					{
						theENEMYTargetPosNode = theENEMYTargetPosNode->right;
						theENEMYCurrentPosNode = theENEMYCurrentPosNode->right;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
					}
					// If target at right side
					else if(theENEMYCurrentPosNode->right == theENEMYTargetPosNode)
					{
						theENEMYTargetPosNode = theENEMYTargetPosNode->left;
						theENEMYCurrentPosNode = theENEMYCurrentPosNode->left;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
					}

					while(theENEMYCurrentPosNode->posType > CPosNode::NONE 
						&& theENEMYCurrentPosNode->posType < CPosNode::ENEMY_INITIAL_POS)
					{
						theENEMYCurrentPosNode = theENEMYTargetPosNode;
						theENEMYPosition = theENEMYCurrentPosNode->pos;
						if(enemyPath.size() != 0)
						{
							theENEMYTargetPosNode = enemyPath.back();
							enemyPath.pop_back();
						}
						else
						{
							theENEMYTargetPosNode = heroPosNode;
						}
					}

				}
			}
			else
			{
				if(currentMode == NIL)
				{
					if((theENEMYCurrentPosNode->pos - theENEMYInitialPosNode->pos).Length() > maxRangeToDetect * 2)
					{
						currentMode = RETURN;
						ReturnCheck(tileSize);
					}
					else
					{
						currentMode = PATROL;
						CheckMode(heroPosNode, tileSize, heroPos);
						if(currentMode == PATROL)
						{
							ChoosePatrolOrIdleMode();
						}
					}
				}
			}
		}
		break;
	case IDLE:
		{
			time -=timeDiff;
			CheckMode(heroPosNode, tileSize, heroPos);
			if(time <= 0.f)
			{
				ChoosePatrolOrIdleMode();
			}
		}
		break;
	}
	if(currentMode != ATTACK)
		UpdateAnimation(theENEMYPosition, theENEMYPrevPosition, timeDiff);
}

void CEnemy::moving(float timeDiff)
{
	theENEMYPosition += vel * timeDiff;
	if((theENEMYPosition - theENEMYCurrentPosNode->pos).Length() > (theENEMYTargetPosNode->pos - theENEMYCurrentPosNode->pos).Length())
	{
		theENEMYPosition = theENEMYTargetPosNode->pos;
		theENEMYCurrentPosNode = theENEMYTargetPosNode;
		currentMode = NIL;
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


vector<CPosNode*> CEnemy::PathFinding(CPosNode* TargetPosNode, int tileSize)
{
	vector<CPosNode*> openList;
	vector<CPosNode*> closedList;
	vector<CPosNode*> deletedList;
	CPosNode* A = theENEMYCurrentPosNode;
	bool start = true;

	openList.push_back(A);

	while(true)
	{
		if(start)
		{
			start = false;
		}
		else
		{
			while(true)
			{
				int smallest_F;
				CPosNode* smallest_F_Node = NULL;
				for(int i = 0; i < openList.size(); ++i)
				{
					if(openList[i]->parent == A)
					{
						smallest_F = Calculate_F(openList[i], TargetPosNode, tileSize, closedList);
						smallest_F_Node = openList[i];
						break;
					}
				}
				for(int i = 0; i < openList.size(); ++i)
				{
					if(openList[i]->parent == A)
					{
						int F = Calculate_F(openList[i], TargetPosNode, tileSize, closedList);
						if(smallest_F > F)
						{
							smallest_F = F;
							smallest_F_Node = openList[i];
						}

					}
				}
				if(smallest_F_Node)
				{
					A = smallest_F_Node;
					break;
				}
				else
				{
					A = A->parent;
					if(A != theENEMYCurrentPosNode)
					{
						deletedList.push_back(A);
						closedList.pop_back();
					}
					else
					{
						break;
					}
				}
			}
		}

		storeAdjacentNodeInList(A, &openList, &closedList, &deletedList,TargetPosNode);

		closedList.push_back(A);
		// Remove A from openList
		for(int i = 0; i < openList.size(); ++i)
		{
			if(openList[i] == A)
			{
				openList[i] = openList.back();
				openList.back() = A;
				openList.pop_back();
			}
		}
		if(TargetPosNode == A
			|| openList.size() == 0)
		{
			break;
		}
	}
	if(TargetPosNode == A)
	{
		vector<CPosNode*> revert;
		while(closedList.size() != 0)
		{
			revert.push_back(closedList.back());
			closedList.pop_back();
		}
		return revert;
	}
	else
	{
		vector<CPosNode*> empty;
		return empty;
	}
}

bool CEnemy::ifNodeInList(CPosNode* posNode, vector<CPosNode*> list)
{
	for(int i = 0; i < list.size(); ++i)
	{
		if(posNode == list[i])
			return true;
	}

	return false;
}

void CEnemy::storeAdjacentNodeInList(CPosNode* posNode, vector<CPosNode*>* openList, vector<CPosNode*>* closedList, vector<CPosNode*>* deletedList, CPosNode* TargetPosNode)
{
	// Top
	if((TargetPosNode->pos - posNode->up->pos).Length() <= maxRangeToDetect
		|| TargetPosNode == theENEMYInitialPosNode)
	{
		if(!ifNodeInList(posNode->up, *openList)
			&& (closedList->size() == 0 || !ifNodeInList(posNode->up, *closedList))
			&& (deletedList->size() == 0 || !ifNodeInList(posNode->up, *deletedList)))
		{
			if(posNode->up->posType == CPosNode::NONE
				|| posNode->up->posType >= CPosNode::ENEMY_INITIAL_POS)
			{
				openList->push_back(posNode->up);
				openList->back()->parent = posNode;
			}
		}
	}
	if((TargetPosNode->pos - posNode->down->pos).Length() <= maxRangeToDetect
		|| TargetPosNode == theENEMYInitialPosNode)
	{
		// Bottom
		if(!ifNodeInList(posNode->down, *openList)
			&& (closedList->size() == 0 || !ifNodeInList(posNode->down, *closedList))
			&& (deletedList->size() == 0 || !ifNodeInList(posNode->down, *deletedList)))
		{
			if(posNode->down->posType == CPosNode::NONE
				|| posNode->down->posType >= CPosNode::ENEMY_INITIAL_POS)
			{
				openList->push_back(posNode->down);
				openList->back()->parent = posNode;
			}
		}
	}
	if((TargetPosNode->pos - posNode->left->pos).Length() <= maxRangeToDetect
		|| TargetPosNode == theENEMYInitialPosNode)
	{	
		// Left
		if(!ifNodeInList(posNode->left, *openList)
			&& (closedList->size() == 0 || !ifNodeInList(posNode->left, *closedList))
			&& (deletedList->size() == 0 || !ifNodeInList(posNode->left, *deletedList)))
		{
			if(posNode->left->posType == CPosNode::NONE
				|| posNode->left->posType >= CPosNode::ENEMY_INITIAL_POS)
			{
				openList->push_back(posNode->left);
				openList->back()->parent = posNode;
			}
		}
	}
	if((TargetPosNode->pos - posNode->right->pos).Length() <= maxRangeToDetect
		|| TargetPosNode == theENEMYInitialPosNode)
	{
		// Right
		if(!ifNodeInList(posNode->right, *openList)
			&& (closedList->size() == 0 || !ifNodeInList(posNode->right, *closedList))
			&& (deletedList->size() == 0 || !ifNodeInList(posNode->right, *deletedList)))
		{
			if(posNode->right->posType == CPosNode::NONE
				|| posNode->right->posType >= CPosNode::ENEMY_INITIAL_POS)
			{
				openList->push_back(posNode->right);
				openList->back()->parent = posNode;
			}
		}
	}
}


int CEnemy::Calculate_G(CPosNode* posNode, vector<CPosNode*> list)
{
	float G = 0;

	for(int i = 1; i < list.size() + 1; ++i)
	{
		G += 10;
	}
	return G;
}

int CEnemy::Calculate_H(CPosNode* CurrentPosNode, CPosNode* TargetPosNode, float tileSize)
{
	float  H_x =  (Vector3(CurrentPosNode->pos.x - TargetPosNode->pos.x)).Length() / tileSize;
	float  H_y =  (Vector3(CurrentPosNode->pos.y - TargetPosNode->pos.y)).Length() / tileSize;

	return H_x + H_y;
}

int CEnemy::Calculate_F(CPosNode* CurrentPosNode, CPosNode* TargetPosNode, float tileSize, vector<CPosNode*> list)
{
	return Calculate_G(CurrentPosNode, list) + Calculate_H(CurrentPosNode, TargetPosNode, tileSize);
}