#include "zombie.h"
#include <iostream>

CZombie::CZombie(void)
	: zombieAnimationDirection(DOWN)
	, zombieAnimationInvert(false)
	, zombieAnimationCounter(0.f)
	, hitHero(false)
	, maxRangeToDetect(0)
	, currentMode(IDLE)
	, time(0)
	, theZombiePosition(Vector3(0,0,0))
	, theZombieInitialPosNode(NULL)
	, theZombieCurrentPosNode(NULL)
	, theZombieTargetPosNode(NULL)
	, vel(Vector3(0,0,0))
	, active(true)
{
}

CZombie::~CZombie(void)
{
	if(theZombieInitialPosNode)
	{
		theZombieInitialPosNode = NULL;
	}
	if(theZombieCurrentPosNode)
	{
		theZombieCurrentPosNode = NULL;
	}
	if(theZombieTargetPosNode)
	{
		theZombieTargetPosNode = NULL;
	}
}


void CZombie::Reset(void)
{
}


// Set position x of the zombie
void CZombie::SetPos_x(float pos_x)
{
	theZombiePosition.x = pos_x;
}

// Set position y of the zombie
void CZombie::SetPos_y(float pos_y)
{
	theZombiePosition.y = pos_y;
}

// Set position of the zombie
void CZombie::SetPos(Vector3 pos)
{
	theZombiePosition.x = pos.x;
	theZombiePosition.y = pos.y;
}

// Set initial position node of the zombie
void CZombie::SetInitialPosNode(CPosNode* posNode)
{
	this->theZombieInitialPosNode = posNode;
}

// Set current position node of the zombie
void CZombie::SetCurrentPosNode(CPosNode* posNode)
{
	this->theZombieCurrentPosNode = posNode;
}

// Set target position node of the zombie
void CZombie::SetTargetPosNode(CPosNode* posNode)
{
	this->theZombieTargetPosNode = posNode;
}


// Get position of the player
Vector3 CZombie::GetPos(void)
{
	return theZombiePosition;
}

// Get current position node of the player
CPosNode* CZombie::GetCurrentPosNode(void)
{
	return theZombieCurrentPosNode;
}

// Get target position node of the player
CPosNode* CZombie::GetTargetPosNode(void)
{
	return theZombieTargetPosNode;
}

// Get velocity of the player
Vector3 CZombie::GetVel(void)
{
	return vel;
}

// Set Animation Invert status of the player
void CZombie::SetAnimationInvert(bool zombieAnimationInvert)
{
	this->zombieAnimationInvert = zombieAnimationInvert;
}

// Get Animation Invert status of the player
bool CZombie::GetAnimationInvert(void)
{
	return zombieAnimationInvert;
}

// Set Animation Counter of the player
void CZombie::SetAnimationCounter(float zombieAnimationCounter)
{
	this->zombieAnimationCounter = zombieAnimationCounter;
}

// Get Animation Counter of the player
float CZombie::GetAnimationCounter(void)
{
	return zombieAnimationCounter;
}

// Set Animation Direction status of the zombie
void CZombie::SetAnimationDirection(ANIMATION_DIRECTION dir)
{
	this->zombieAnimationDirection = dir;
}

CZombie::ANIMATION_DIRECTION CZombie::GetAnimationDirection(void)
{
	return zombieAnimationDirection;
}


void CZombie::SetCurrentMode(CZombie::CURRENT_MODE currentMode)
{
	this->currentMode = currentMode;
}

CZombie::CURRENT_MODE CZombie::GetCurrentMode(void)
{
	return currentMode;
}

void CZombie::SetHitHero(bool hitHero)
{
	this->hitHero = hitHero;
}

bool CZombie::GetHitHero(void)
{
	return hitHero;
}

void CZombie::SetMaxRangeToDetect(int maxRangeToDetect)
{
	this->maxRangeToDetect = maxRangeToDetect;
}

int CZombie::GetMaxRangeToDetect(void)
{
	return maxRangeToDetect;
}

// Set time of the zombie
void CZombie::SetTime(float time)
{
	this->time = time;
}

// Get time of the zombie
float CZombie::GetTime(void)
{
	return time;
}

// Set health of the zombie
void CZombie::SetHealth(int health)
{
	this->health = health;
}

// Get health of the zombie
int CZombie::GetHealth(void)
{
	return health;
}

// Check current mode
void CZombie::CheckMode(CPosNode* heroPosNode, int tileSize, Vector3 heroPos)
{
	float DistFromHeroTozombie = (theZombiePosition - heroPos).Length();
	float DistFromHeroTozombieInit = (heroPos - theZombieInitialPosNode->pos).Length();
	// If within range of detection
	if(checkIfHeroIsWithinSight(heroPos) && DistFromHeroTozombieInit <= maxRangeToDetect * 2
		|| (checkIfHeroIsWithinSight(heroPos) && zombie_type != SMART))
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
			if(zombiePath.size() == 0 || zombiePath[0] != heroPosNode)
			{
				// Find a path
				zombiePath = PathFinding(heroPosNode, tileSize);
				ChaseCheck(heroPosNode, tileSize);
			}
			else
			{
				theZombieTargetPosNode = zombiePath.back();
				zombiePath.pop_back();
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
			// if theZombieCurrentPosNode not equal to theZombieInitialPosNode
			if(theZombieCurrentPosNode != theZombieInitialPosNode)
			{
				theZombieTargetPosNode = zombiePath.back();
				zombiePath.pop_back();
				CalculateVel();
				currentMode = RETURN;
			}
			// if theZombieCurrentPosNode equal to theZombieInitialPosNode
			else
			{
				ChoosePatrolOrIdleMode();
			}
		}
	}
}

void CZombie::ChaseCheck(CPosNode* heroPosNode, int tileSize)
{
	// Find a path
	zombiePath = PathFinding(heroPosNode, tileSize);
	// if path not empty
	if(zombiePath.size() != 0)
	{
		// if theZombieTargetPosNode is equal to next path node
		if(theZombieTargetPosNode == zombiePath.back())
		{
			zombiePath.pop_back();
		}
		if(zombiePath.size() != 0)
		{
			theZombieTargetPosNode = zombiePath.back();
			zombiePath.pop_back();
			CalculateVel();
		}
	}
	// if path is empty
	else
	{
		ReturnCheck(tileSize);
	}
}

void CZombie::ReturnCheck(int tileSize)
{
	// if zombie is a smart type
	if((zombie_type == SMART)
	// if theZombieCurrentPosNode is not theZombieInitialPosNode
		&& theZombieCurrentPosNode != theZombieInitialPosNode)
	{
		// Mode = RETURN
		currentMode = RETURN;
		// Find a path
		zombiePath = PathFinding(theZombieInitialPosNode, tileSize);
		// if path not empty
		if(zombiePath.size() != 0)
		{
			// if theZombieTargetPosNode is equal to next path node
			if(theZombieTargetPosNode == zombiePath.back())
			{
				zombiePath.pop_back();
			}
			if(zombiePath.size() != 0)
			{
				theZombieTargetPosNode = zombiePath.back();
				zombiePath.pop_back();
				CalculateVel();
			}
		}
		else
		{
			// if path is empty
			ChoosePatrolOrIdleMode();
		}
	}
	// if theZombieCurrentPosNode is theZombieInitialPosNode
	else
	{
		ChoosePatrolOrIdleMode();
	}
}


bool CZombie::checkIfHeroIsWithinSight(Vector3 heroPos)
{
	// if within radius
	if((theZombiePosition - heroPos).Length() <= maxRangeToDetect)
	{
		// if zombie looking up and hero is on top
		if((zombieAnimationDirection == UP) && (heroPos.y >= theZombiePosition.y)
			// if zombie looking down and hero is below
			||(zombieAnimationDirection == DOWN) && (heroPos.y <= theZombiePosition.y)
			// if zombie looking left and hero is on the left
			||(zombieAnimationDirection == LEFT) && (heroPos.x <= theZombiePosition.x)
			// if zombie looking right and hero is on the right
			||(zombieAnimationDirection == RIGHT) && (heroPos.x >= theZombiePosition.x)
			// if zombie is a TANK type
			|| zombie_type == TANK
			// if zombie is a hunter type
			|| zombie_type == HUNTER)
		{
		//	// Check above
		//	if((heroPos.y > theZombiePosition.y
		//		&& theZombieCurrentPosNode->up->posType != CPosNode::NONE
		//		&& theZombieCurrentPosNode->up->posType >= CPosNode::HERO_INIT_POS)
		//		||(heroPos.y < theZombiePosition.y
		//		&& theZombieCurrentPosNode->down->posType != CPosNode::NONE
		//		&& theZombieCurrentPosNode->down->posType >= CPosNode::HERO_INIT_POS)
		//		|| (heroPos.x < theZombiePosition.x
		//		&& theZombieCurrentPosNode->left->posType != CPosNode::NONE
		//		&& theZombieCurrentPosNode->left->posType >= CPosNode::HERO_INIT_POS)
		//		||(heroPos.x > theZombiePosition.x
		//		&& theZombieCurrentPosNode->right->posType != CPosNode::NONE
		//		&& theZombieCurrentPosNode->right->posType >= CPosNode::HERO_INIT_POS))
			{
				return true;
			}
		}
	}

	// If not within sight
	return false;
}


// Choose patrol or idle mode
void CZombie::ChoosePatrolOrIdleMode(void)
{
	if(rand() % 2 == 0)
	{
		currentMode = PATROL;
		while(true)
		{
			int temp = rand() % 4;
			if(temp == 0)
			{
				theZombieTargetPosNode = theZombieTargetPosNode->up;
			}
			else if(temp == 1)
			{
				theZombieTargetPosNode = theZombieTargetPosNode->down;
			}
			else if(temp == 2)
			{
				theZombieTargetPosNode = theZombieTargetPosNode->left;
			}
			else
			{
				theZombieTargetPosNode = theZombieTargetPosNode->right;
			}
			if(theZombieTargetPosNode->posType == CPosNode::NONE
				|| theZombieTargetPosNode->posType > CPosNode::TOTAL_ACTIVE_GO)
			{
				CalculateVel();
				break;
			}
			theZombieTargetPosNode = theZombieCurrentPosNode;
		}
	}
	else
	{
		currentMode = IDLE;
		time = Math::RandFloatMinMax(1, 2);
	}
}

void CZombie::CalculateVel(void)
{
	if(theZombieCurrentPosNode->up == theZombieTargetPosNode)
	{
		vel.Set(0, movementSpeed, 0);
	}
	else if(theZombieCurrentPosNode->down == theZombieTargetPosNode)
	{
		vel.Set(0, -movementSpeed, 0);
	}
	else if(theZombieCurrentPosNode->left == theZombieTargetPosNode)
	{
		vel.Set(-movementSpeed, 0, 0);
	}
	else if(theZombieCurrentPosNode->right == theZombieTargetPosNode)
	{
		vel.Set(movementSpeed, 0, 0);
	}
}

bool CZombie::AttackCheck(CPosNode* heroPosNode, Vector3 heroPos, int tileSize)
{
	float DistFromHeroTozombie = (theZombiePosition - heroPos).Length();
	// If within range of attack
	if(DistFromHeroTozombie <= tileSize * 0.5)
	{
		// If not attack
		if(currentMode != ATTACK)
		{
			currentMode = ATTACK;
			hitHero = true;
			time = 0.5f;
			zombiePath.push_back(theZombieTargetPosNode);

			// If target at up side
			if(theZombieCurrentPosNode->up == theZombieTargetPosNode)
			{
				theZombieTargetPosNode = theZombieTargetPosNode->down;
				theZombieCurrentPosNode = theZombieCurrentPosNode->down;
				theZombiePosition = theZombieCurrentPosNode->pos;
			}
			// If target at down side
			else if(theZombieCurrentPosNode->down == theZombieTargetPosNode)
			{
				theZombieTargetPosNode = theZombieTargetPosNode->up;
				theZombieCurrentPosNode = theZombieCurrentPosNode->up;
				theZombiePosition = theZombieCurrentPosNode->pos;
			}
			// If target at left side
			else if(theZombieCurrentPosNode->left == theZombieTargetPosNode)
			{
				theZombieTargetPosNode = theZombieTargetPosNode->right;
				theZombieCurrentPosNode = theZombieCurrentPosNode->right;
				theZombiePosition = theZombieCurrentPosNode->pos;
			}
			// If target at right side
			else if(theZombieCurrentPosNode->right == theZombieTargetPosNode)
			{
				theZombieTargetPosNode = theZombieTargetPosNode->left;
				theZombieCurrentPosNode = theZombieCurrentPosNode->left;
				theZombiePosition = theZombieCurrentPosNode->pos;
			}

			while(theZombieCurrentPosNode->posType > CPosNode::NONE 
				&& theZombieCurrentPosNode->posType < CPosNode::NORMAL_ZOMBIE_INITIAL_POS)
			{
				theZombieCurrentPosNode = theZombieTargetPosNode;
				theZombiePosition = theZombieCurrentPosNode->pos;
				if(zombiePath.size() != 0)
				{
					theZombieTargetPosNode = zombiePath.back();
					zombiePath.pop_back();
				}
				else
				{
					theZombieTargetPosNode = heroPosNode;
				}
			}
			return true;
		}
	}
	else
	{
		return false;
	}
}

/********************************************************************************
Hero Update
********************************************************************************/
void CZombie::Update(int tileSize, float timeDiff, CPosNode* heroPosNode, Vector3 heroPos)
{
	Vector3 theZombiePrevPosition = theZombiePosition;
	switch(currentMode)
	{
	case CHASE:
		{
			moving(timeDiff);
			if(!AttackCheck(heroPosNode, heroPos, tileSize))
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
			if(!AttackCheck(heroPosNode, heroPos, tileSize))
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
			if(!AttackCheck(heroPosNode, heroPos, tileSize))
			{
				if(currentMode == NIL)
				{
					if((theZombieCurrentPosNode->pos - theZombieInitialPosNode->pos).Length() > maxRangeToDetect * 2)
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
		UpdateAnimation(theZombiePosition, theZombiePrevPosition, timeDiff);
}

void CZombie::moving(float timeDiff)
{
	theZombiePosition += vel * timeDiff;
	if((theZombiePosition - theZombieCurrentPosNode->pos).Length() > (theZombieTargetPosNode->pos - theZombieCurrentPosNode->pos).Length())
	{
		theZombiePosition = theZombieTargetPosNode->pos;
		theZombieCurrentPosNode = theZombieTargetPosNode;
		currentMode = NIL;
	}
}

void CZombie::UpdateAnimation(Vector3 CurrentPos, Vector3 PrevPos, float timeDiff)
{
	if(CurrentPos.y > PrevPos.y)
	{
		zombieAnimationDirection = UP;
		zombieAnimationInvert = false;
		zombieAnimationCounter += animationSpeed * timeDiff;
		if(zombieAnimationCounter > 2.0f)
			zombieAnimationCounter = 0.0f;
	}
	else if(CurrentPos.y < PrevPos.y)
	{
		zombieAnimationDirection = DOWN;
		zombieAnimationInvert = false;
		zombieAnimationCounter += animationSpeed * timeDiff;
		if(zombieAnimationCounter > 2.0f)
			zombieAnimationCounter = 0.0f;
	}
	else if(CurrentPos.x < PrevPos.x)
	{
		zombieAnimationDirection = LEFT;
		zombieAnimationInvert = true;
		zombieAnimationCounter -= animationSpeed * timeDiff;
		if(zombieAnimationCounter < 0.0f)
			zombieAnimationCounter = 2.0f;
	}
	else if(CurrentPos.x > PrevPos.x)
	{
		zombieAnimationDirection = RIGHT;
		zombieAnimationInvert = false;
		zombieAnimationCounter += animationSpeed * timeDiff;
		if(zombieAnimationCounter > 2.0f)
			zombieAnimationCounter = 0.0f;
	}
}


vector<CPosNode*> CZombie::PathFinding(CPosNode* TargetPosNode, int tileSize)
{
	vector<CPosNode*> openList;
	vector<CPosNode*> closedList;
	vector<CPosNode*> deletedList;
	CPosNode* A = theZombieCurrentPosNode;
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
					if(A != theZombieCurrentPosNode)
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

bool CZombie::ifNodeInList(CPosNode* posNode, vector<CPosNode*> list)
{
	for(int i = 0; i < list.size(); ++i)
	{
		if(posNode == list[i])
			return true;
	}

	return false;
}

void CZombie::storeAdjacentNodeInList(CPosNode* posNode, vector<CPosNode*>* openList, vector<CPosNode*>* closedList, vector<CPosNode*>* deletedList, CPosNode* TargetPosNode)
{
	// Top
	if((TargetPosNode->pos - posNode->up->pos).Length() <= maxRangeToDetect
		|| TargetPosNode == theZombieInitialPosNode)
	{
		if(!ifNodeInList(posNode->up, *openList)
			&& (closedList->size() == 0 || !ifNodeInList(posNode->up, *closedList))
			&& (deletedList->size() == 0 || !ifNodeInList(posNode->up, *deletedList)))
		{
			if(posNode->up->posType == CPosNode::NONE
				|| posNode->up->posType >= CPosNode::HERO_INIT_POS)
			{
				openList->push_back(posNode->up);
				openList->back()->parent = posNode;
			}
		}
	}
	if((TargetPosNode->pos - posNode->down->pos).Length() <= maxRangeToDetect
		|| TargetPosNode == theZombieInitialPosNode)
	{
		// Bottom
		if(!ifNodeInList(posNode->down, *openList)
			&& (closedList->size() == 0 || !ifNodeInList(posNode->down, *closedList))
			&& (deletedList->size() == 0 || !ifNodeInList(posNode->down, *deletedList)))
		{
			if(posNode->down->posType == CPosNode::NONE
				|| posNode->down->posType >= CPosNode::HERO_INIT_POS)
			{
				openList->push_back(posNode->down);
				openList->back()->parent = posNode;
			}
		}
	}
	if((TargetPosNode->pos - posNode->left->pos).Length() <= maxRangeToDetect
		|| TargetPosNode == theZombieInitialPosNode)
	{	
		// Left
		if(!ifNodeInList(posNode->left, *openList)
			&& (closedList->size() == 0 || !ifNodeInList(posNode->left, *closedList))
			&& (deletedList->size() == 0 || !ifNodeInList(posNode->left, *deletedList)))
		{
			if(posNode->left->posType == CPosNode::NONE
				|| posNode->left->posType >= CPosNode::HERO_INIT_POS)
			{
				openList->push_back(posNode->left);
				openList->back()->parent = posNode;
			}
		}
	}
	if((TargetPosNode->pos - posNode->right->pos).Length() <= maxRangeToDetect
		|| TargetPosNode == theZombieInitialPosNode)
	{
		// Right
		if(!ifNodeInList(posNode->right, *openList)
			&& (closedList->size() == 0 || !ifNodeInList(posNode->right, *closedList))
			&& (deletedList->size() == 0 || !ifNodeInList(posNode->right, *deletedList)))
		{
			if(posNode->right->posType == CPosNode::NONE
				|| posNode->right->posType >= CPosNode::HERO_INIT_POS)
			{
				openList->push_back(posNode->right);
				openList->back()->parent = posNode;
			}
		}
	}
}


int CZombie::Calculate_G(CPosNode* posNode, vector<CPosNode*> list)
{
	float G = 0;

	for(int i = 1; i < list.size() + 1; ++i)
	{
		G += 10;
	}
	return G;
}

int CZombie::Calculate_H(CPosNode* CurrentPosNode, CPosNode* TargetPosNode, float tileSize)
{
	float  H_x =  (Vector3(CurrentPosNode->pos.x - TargetPosNode->pos.x)).Length() / tileSize;
	float  H_y =  (Vector3(CurrentPosNode->pos.y - TargetPosNode->pos.y)).Length() / tileSize;

	return H_x + H_y;
}

int CZombie::Calculate_F(CPosNode* CurrentPosNode, CPosNode* TargetPosNode, float tileSize, vector<CPosNode*> list)
{
	return Calculate_G(CurrentPosNode, list) + Calculate_H(CurrentPosNode, TargetPosNode, tileSize);
}