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
	, movementSpeed(100.0f)
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


// Check current mode
void CEnemy::CheckMode(CPosNode* heroPosNode, int tileSize)
{
	float DistFromHeroToEnemy = (theENEMYPosition - heroPosNode->pos).Length();
	// If within range of detection
	if(DistFromHeroToEnemy <= maxRangeToDetect)
	{
		// If within range of attack
		if(DistFromHeroToEnemy <= tileSize * 0.25)
		{
			// If not attack
			if(currentMode != ATTACK)
			{
				currentMode = ATTACK;
				hitHero = true;
				time = 2;
			}
		}
		else
		{
			// If not chase
			if(currentMode != CHASE && currentMode != ATTACK)
			{
				currentMode = CHASE;
				enemyPath = PathFinding(heroPosNode, tileSize);
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
			currentMode = RETURN;
			enemyPath = PathFinding(theENEMYInitialPosNode, tileSize);
			if(enemyPath.size() != 0)
			{
				theENEMYTargetPosNode = enemyPath.back();
				enemyPath.pop_back();
				CalculateVel();
			}
			else
			{
				ChoosePatrolOrIdleMode();
			}
		}
	}
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
void CEnemy::Update(int tileSize, float timeDiff, CPosNode* heroPosNode)
{
	Vector3 theENEMYPrevPosition = theENEMYPosition;
	switch(currentMode)
	{
	case CHASE:
		{
			moving(timeDiff);
			if(currentMode == NIL)
			{
				if(enemyPath.size() == 0 || enemyPath[0] != heroPosNode)
				{
					enemyPath = PathFinding(heroPosNode, tileSize);
				}
				theENEMYTargetPosNode = enemyPath.back();
				enemyPath.pop_back();
				CalculateVel();
			}
		}
		break;
	case ATTACK:
		{
			time -=timeDiff;
			if(time <= 0.f)
			{
				currentMode = CHASE;
				enemyPath = PathFinding(heroPosNode, tileSize);
				theENEMYTargetPosNode = enemyPath.back();
				enemyPath.pop_back();
				CalculateVel();
			}
		}
		break;
	case RETURN:
		{
			moving(timeDiff);
			if(currentMode == NIL)
			{
				if(theENEMYTargetPosNode != theENEMYInitialPosNode)
				{
					theENEMYTargetPosNode = enemyPath.back();
					enemyPath.pop_back();
					CalculateVel();
				}
				else
				{
					ChoosePatrolOrIdleMode();
				}
			}
		}
		break;
	case PATROL:
		{
			moving(timeDiff);
			if(currentMode == NIL)
			{
				ChoosePatrolOrIdleMode();
			}
		}
		break;
	case IDLE:
		{
			time -=timeDiff;
			if(time <= 0.f)
			{
				ChoosePatrolOrIdleMode();
			}
		}
		break;
	}
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

CEnemy::ANIMATION_DIRECTION CEnemy::GetAnimationDirection(void)
{
	return enemyAnimationDirection;
}


vector<CPosNode*> CEnemy::PathFinding(CPosNode* TargetPosNode, int tileSize)
{
	vector<CPosNode*> openList;
	vector<CPosNode*> closedList;
	CPosNode* A = TargetPosNode;
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
			int smallest_F;
			CPosNode* smallest_F_Node = NULL;
			for(int i = 0; i < openList.size(); ++i)
			{
				if(openList[i]->parent == A)
				{
					smallest_F = Calculate_F(openList[i], theENEMYCurrentPosNode, tileSize, closedList);
					smallest_F_Node = openList[i];
					break;
				}
			}
			for(int i = 0; i < openList.size(); ++i)
			{
				if(openList[i]->parent == A)
				{
					int F = Calculate_F(openList[i], theENEMYCurrentPosNode, tileSize, closedList);
					if(smallest_F > F)
					{
						smallest_F = F;
						smallest_F_Node = openList[i];
					}

				}
			}

			A = smallest_F_Node;
		}

		storeAdjacentNodeInList(A, &openList, &closedList);

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
		if(theENEMYCurrentPosNode == A
			|| openList.size() == 0)
		{
			break;
		}
	}

	closedList.pop_back();

	return closedList;
}
//	CPosNode* current;
//	vector<CPosNode*> path;
//	vector<vector<CPosNode*>> allPath;
//	current = TargetPosNode;
//	allPath.push_back(path);
//	allPath[0].push_back(current);
//
//	// Store path
//	for(int i = 0; i < allPath.size(); i++)
//	{
//		current = allPath[i].back();
//		while(true)
//		{
//			// Check enemy pos
//			if(current->pos.y < theENEMYCurrentPosNode->pos.y)
//			{
//				// Check up
//				if(current->up->posType == CPosNode::NONE
//					|| current->up->posType >= CPosNode::ENEMY_INITIAL_POS)
//				{
//					current = current->up;
//					allPath[i].push_back(current);
//				}
//				// Check if  enemy pos is left
//				else if(current->pos.x < theENEMYCurrentPosNode->pos.x)
//				{
//					// Check left
//					if(current->left->posType == CPosNode::NONE
//						|| current->left->posType >= CPosNode::ENEMY_INITIAL_POS)
//					{
//						current = current->left;
//						allPath[i].push_back(current);
//					}
//				}
//				// or on right
//				else if(current->pos.x > theENEMYCurrentPosNode->pos.x)
//				{
//				}
//				else
//				{
//					// Check left
//					if(current->left->posType == CPosNode::NONE
//						|| current->left->posType >= CPosNode::ENEMY_INITIAL_POS)
//					{
//						// Check right
//						if(current->right->posType == CPosNode::NONE
//							|| current->right->posType >= CPosNode::ENEMY_INITIAL_POS)
//						{
//							current = current->right;
//
//							int i;
//							for(i = 0; i < allPath.size(); ++i)
//							{
//								if(ifNodeInPath(current, allPath[i]))
//								{
//									break;
//								}
//							}
//							if(i == allPath.size())
//								allPath.push_back(allPath[i]);
//
//							current = current->left;
//						}
//						current = current->left;
//						allPath[i].push_back(current);
//					}
//					// Check right
//					else if(current->right->posType == CPosNode::NONE
//						|| current->right->posType >= CPosNode::ENEMY_INITIAL_POS)
//					{
//						current = current->right;
//						allPath[i].push_back(current);
//					}
//				}
//			}
//			//
//
//
//
//
//			else if(current->pos.y > theENEMYCurrentPosNode->pos.y)
//			{
//				// Check down
//				if(current->down->posType == CPosNode::NONE
//					|| current->down->posType >= CPosNode::ENEMY_INITIAL_POS)
//				{
//					current = current->down;
//					allPath[i].push_back(current);
//				}
//				// Check left
//				else if(current->left->posType == CPosNode::NONE
//					|| current->left->posType >= CPosNode::ENEMY_INITIAL_POS)
//				{
//					// Check right
//					if(current->right->posType == CPosNode::NONE
//						|| current->right->posType >= CPosNode::ENEMY_INITIAL_POS)
//					{
//						current = current->right;
//
//						int i;
//						for(i = 0; i < allPath.size(); ++i)
//						{
//							if(ifNodeInPath(current, allPath[i]))
//							{
//								break;
//							}
//						}
//						if(i == allPath.size())
//							allPath.push_back(allPath[i]);
//
//						current = current->left;
//					}
//					current = current->left;
//					allPath[i].push_back(current);
//				}
//				// Check right
//				else if(current->right->posType == CPosNode::NONE
//					|| current->right->posType >= CPosNode::ENEMY_INITIAL_POS)
//				{
//					current = current->right;
//					allPath[i].push_back(current);
//				}
//			}
//			else if(current->pos.x > theENEMYCurrentPosNode->pos.x)
//			{
//				// Check left
//				if(current->left->posType == CPosNode::NONE
//					|| current->left->posType >= CPosNode::ENEMY_INITIAL_POS)
//				{
//					current = current->left;
//					allPath[i].push_back(current);
//				}
//				// Check up
//				else if(current->up->posType == CPosNode::NONE
//					|| current->up->posType >= CPosNode::ENEMY_INITIAL_POS)
//				{
//					// Check right
//					if(current->down->posType == CPosNode::NONE
//						|| current->down->posType >= CPosNode::ENEMY_INITIAL_POS)
//					{
//						current = current->down;
//
//						int i;
//						for(i = 0; i < allPath.size(); ++i)
//						{
//							if(ifNodeInPath(current, allPath[i]))
//							{
//								break;
//							}
//						}
//						if(i == allPath.size())
//							allPath.push_back(allPath[i]);
//
//						current = current->up;
//					}
//					current = current->up;
//					allPath[i].push_back(current);
//				}
//				// Check right
//				else if(current->down->posType == CPosNode::NONE
//					|| current->down->posType >= CPosNode::ENEMY_INITIAL_POS)
//				{
//					current = current->down;
//					allPath[i].push_back(current);
//				}
//			}
//			else if(current->pos.x < theENEMYCurrentPosNode->pos.x)
//			{
//				// Check right
//				if(current->right->posType == CPosNode::NONE
//					|| current->right->posType >= CPosNode::ENEMY_INITIAL_POS)
//				{
//					current = current->right;
//					allPath[i].push_back(current);
//				}
//				// Check up
//				else if(current->up->posType == CPosNode::NONE
//					|| current->up->posType >= CPosNode::ENEMY_INITIAL_POS)
//				{
//					// Check right
//					if(current->down->posType == CPosNode::NONE
//						|| current->down->posType >= CPosNode::ENEMY_INITIAL_POS)
//					{
//						current = current->down;
//
//						int i;
//						for(i = 0; i < allPath.size(); ++i)
//						{
//							if(ifNodeInPath(current, allPath[i]))
//							{
//								break;
//							}
//						}
//						if(i == allPath.size())
//							allPath.push_back(allPath[i]);
//
//						current = current->up;
//					}
//					current = current->up;
//					allPath[i].push_back(current);
//				}
//				// Check right
//				else if(current->down->posType == CPosNode::NONE
//					|| current->down->posType >= CPosNode::ENEMY_INITIAL_POS)
//				{
//					current = current->down;
//					allPath[i].push_back(current);
//				}
//			}
//			if(current == theENEMYCurrentPosNode)
//			{
//				allPath[i].pop_back();
//				break;
//			}
//		}
//	}
//
//	// Get shortest rout
//	vector<CPosNode*> shortest = allPath[0];
//	for(int i = 1; i < allPath.size(); i++)
//	{
//		if(shortest.size() > allPath[i].size())
//		{
//			shortest = allPath[i];
//		}
//	}
//
//	return shortest;



bool CEnemy::ifNodeInList(CPosNode* posNode, vector<CPosNode*> list)
{
	for(int i = 0; i < list.size(); ++i)
	{
		if(posNode == list[i])
			return true;
	}

	return false;
}

void CEnemy::storeAdjacentNodeInList(CPosNode* posNode, vector<CPosNode*>* openList, vector<CPosNode*>* closedList)
{
	// Top
	if(!ifNodeInList(posNode->up, *openList) 
		&& (closedList->size() == 0 || !ifNodeInList(posNode->up, *closedList)))
	{
		if(posNode->up->posType == CPosNode::NONE
			|| posNode->up->posType >= CPosNode::ENEMY_INITIAL_POS)
		{
			openList->push_back(posNode->up);
			openList->back()->parent = posNode;
		}
	}
	// Bottom
	if(!ifNodeInList(posNode->down, *openList)
		&& (closedList->size() == 0 || !ifNodeInList(posNode->down, *closedList)))
	{
		if(posNode->down->posType == CPosNode::NONE
			|| posNode->down->posType >= CPosNode::ENEMY_INITIAL_POS)
		{
			openList->push_back(posNode->down);
			openList->back()->parent = posNode;
		}
	}	
	// Left
	if(!ifNodeInList(posNode->left, *openList)
		&& (closedList->size() == 0 || !ifNodeInList(posNode->left, *closedList)))
	{
		if(posNode->left->posType == CPosNode::NONE
			|| posNode->left->posType >= CPosNode::ENEMY_INITIAL_POS)
		{
			openList->push_back(posNode->left);
			openList->back()->parent = posNode;
		}
	}
	// Right
	if(!ifNodeInList(posNode->right, *openList)
		&& (closedList->size() == 0 || !ifNodeInList(posNode->right, *closedList)))
	{
		if(posNode->right->posType == CPosNode::NONE
			|| posNode->right->posType >= CPosNode::ENEMY_INITIAL_POS)
		{
			openList->push_back(posNode->right);
			openList->back()->parent = posNode;
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