#include "PlayerInfo.h"
#include <iostream>


CPlayerInfo::CPlayerInfo(void)
	: theHeroPosition(Vector3(0, 0, 0))
	, movementSpeed(200.0f)
	, currentState(NIL)
	, timeElasped(0.f)
	, heroAnimationDirection(DOWN)
	, heroAnimationCounter(0.0f)
	, heroAnimationInvert(false)
	, heroAnimationSpeed(20)
	, health(3)
	, theHeroInitialPosNode(NULL)
	, theHeroCurrentPosNode(NULL)
	, theHeroTargetPosNode(NULL)
	, vel(Vector3(0,0,0))
{
}


CPlayerInfo::~CPlayerInfo(void)
{
	if(theHeroInitialPosNode)
	{
		theHeroInitialPosNode = NULL;
	}
	if(theHeroCurrentPosNode)
	{
		theHeroCurrentPosNode = NULL;
	}
	if(theHeroTargetPosNode)
	{
		theHeroTargetPosNode = NULL;
	}
	for(int i = 0; i < frontMeshes.size(); ++i)
	{
		if(frontMeshes[i])
		{
			delete frontMeshes[i];
			frontMeshes[i] = NULL;
		}
	}
	for(int i = 0; i < backMeshes.size(); ++i)
	{
		if(backMeshes[i])
		{
			delete backMeshes[i];
			backMeshes[i] = NULL;
		}
	}
	for(int i = 0; i < sideMeshes.size(); ++i)
	{
		if(sideMeshes[i])
		{
			delete sideMeshes[i];
			sideMeshes[i] = NULL;
		}
	}
	for(int i = 0; i < deathMeshes.size(); ++i)
	{
		if(deathMeshes[i])
		{
			delete deathMeshes[i];
			deathMeshes[i] = NULL;
		}
	}
	for(int i = 0; i < attackFrontMeshes.size(); ++i)
	{
		if(attackFrontMeshes[i])
		{
			delete attackFrontMeshes[i];
			attackFrontMeshes[i] = NULL;
		}
	}
	for(int i = 0; i < attackBackMeshes.size(); ++i)
	{
		if(attackBackMeshes[i])
		{
			delete attackBackMeshes[i];
			attackBackMeshes[i] = NULL;
		}
	}
	for(int i = 0; i < attackSideMeshes.size(); ++i)
	{
		if(attackSideMeshes[i])
		{
			delete attackSideMeshes[i];
			attackSideMeshes[i] = NULL;
		}
	}
}


void CPlayerInfo::Reset(void)
{
	theHeroPosition = theHeroInitialPosNode->pos;
	theHeroCurrentPosNode = theHeroInitialPosNode;
	theHeroTargetPosNode = theHeroCurrentPosNode;

	currentState = CPlayerInfo::NIL;

	timeElasped = 0.f;

	heroAnimationDirection = DOWN;
	heroAnimationCounter = 0.0f;
	heroAnimationInvert = false;
	heroAnimationSpeed = 20;

	health = 3;
}

// Set position x of the player
void CPlayerInfo::SetPos_x(float pos_x)
{
	theHeroPosition.x = pos_x;
}

// Set position y of the player
void CPlayerInfo::SetPos_y(float pos_y)
{
	theHeroPosition.y = pos_y;
}

// Set position of the player
void CPlayerInfo::SetPos(Vector3 pos)
{
	theHeroPosition.x = pos.x;
	theHeroPosition.y = pos.y;
}

// Set initial position node of the player
void CPlayerInfo::SetInitialPosNode(CPosNode* posNode)
{
	this->theHeroInitialPosNode = posNode;
}

// Set current position node of the player
void CPlayerInfo::SetCurrentPosNode(CPosNode* posNode)
{
	this->theHeroCurrentPosNode = posNode;
}

// Set target position node of the player
void CPlayerInfo::SetTargetPosNode(CPosNode* posNode)
{
	this->theHeroTargetPosNode = posNode;
}


// Get position of the player
Vector3 CPlayerInfo::GetPos(void)
{
	return theHeroPosition;
}

// Get current position node of the player
CPosNode* CPlayerInfo::GetCurrentPosNode(void)
{
	return theHeroCurrentPosNode;
}

// Get target position node of the player
CPosNode* CPlayerInfo::GetTargetPosNode(void)
{
	return theHeroTargetPosNode;
}


// Set Animation Direction status of the player
void CPlayerInfo::SetAnimationDirection(ANIMATION_DIRECTION heroAnimationDirection)
{
	this->heroAnimationDirection = heroAnimationDirection;
}

// Get Animation Direction status of the player
CPlayerInfo::ANIMATION_DIRECTION CPlayerInfo::GetAnimationDirection(void)
{
	return heroAnimationDirection;
}

// Set Animation Invert status of the player
void CPlayerInfo::SetAnimationInvert(bool heroAnimationInvert)
{
	this->heroAnimationInvert = heroAnimationInvert;
}

// Get Animation Invert status of the player
bool CPlayerInfo::GetAnimationInvert(void)
{
	return heroAnimationInvert;
}

// Set Animation Counter of the player
void CPlayerInfo::SetAnimationCounter(float heroAnimationCounter)
{
	this->heroAnimationCounter = heroAnimationCounter;
}

// Get Animation Counter of the player
float CPlayerInfo::GetAnimationCounter(void)
{
	return heroAnimationCounter;
}


void CPlayerInfo::SetCurrentState(CPlayerInfo::CURRENT_STATE currentState)
{
	this->currentState = currentState;
}

CPlayerInfo::CURRENT_STATE CPlayerInfo::GetCurrentState(void)
{
	return currentState;
}


void CPlayerInfo::SetTimeElasped(float timeElasped)
{
	this->timeElasped = timeElasped;
}

float CPlayerInfo::GetTimeElasped(void)
{
	return timeElasped;
}


void CPlayerInfo::SetHealth(int health)
{
	this->health = health;
}

int CPlayerInfo::GetHealth(void)
{
	return health;
}


/********************************************************************************
Hero Move Up Down
********************************************************************************/
void CPlayerInfo::MoveUpDown(const bool mode)
{
	if (mode)
	{
		theHeroTargetPosNode = theHeroTargetPosNode->up;
		if(!CPlayerInfo::CheckCollisionTarget())
		{
			vel.Set(0, movementSpeed, 0);
			currentState = MOVING;
		}
		else
		{
			theHeroTargetPosNode = theHeroCurrentPosNode;
		}
	}
	else
	{
		theHeroTargetPosNode = theHeroTargetPosNode->down;
		if(!CPlayerInfo::CheckCollisionTarget())
		{
			vel.Set(0, -movementSpeed, 0);
			currentState = MOVING;
		}
		else
		{
			theHeroTargetPosNode = theHeroCurrentPosNode;
		}
	}
}

/********************************************************************************
Hero Move Left Right
********************************************************************************/
void CPlayerInfo::MoveLeftRight(const bool mode)
{
	if (mode)
	{
		theHeroTargetPosNode = theHeroTargetPosNode->left;
		if(!CPlayerInfo::CheckCollisionTarget())
		{
			vel.Set(-movementSpeed, 0, 0);
			currentState = MOVING;
		}
		else
		{
			theHeroTargetPosNode = theHeroCurrentPosNode;
		}
	}
	else
	{
		theHeroTargetPosNode = theHeroTargetPosNode->right;
		if(!CPlayerInfo::CheckCollisionTarget())
		{
			vel.Set(movementSpeed, 0, 0);
			currentState = MOVING;
		}
		else
		{
			theHeroTargetPosNode = theHeroCurrentPosNode;
		}
	}
}


/********************************************************************************
Hero Update
********************************************************************************/
void CPlayerInfo::HeroUpdate(float timeDiff, CAIManager* ai_manager, GameObjectFactory* go_manager)
{
	// Update Hero's info
	switch(currentState)
	{
	case CPlayerInfo::KNOCKED_BACKING:
		{
			moving(timeDiff);
		}
		break;
	case CPlayerInfo::ATTACKING:
		{
			Attacking(timeDiff, ai_manager, go_manager);
		}
		break;
	default:
		{
			Vector3 HeroPrevPos = theHeroPosition;
			moving(timeDiff);
			if(currentState == MOVING)
				moveAnimation(timeDiff, HeroPrevPos);
		}
		break;
	}
	if(currentState == NIL)
	{
		if(CheckCollisionCurrent())
		{
			CollisionResponseCurrent();
		}
	}
}


void CPlayerInfo::knockBackEnabled(Vector3 AI_Pos)
{
	if(theHeroCurrentPosNode == theHeroTargetPosNode)
	{
		if(AI_Pos.y > theHeroCurrentPosNode->pos.y)
		{
			theHeroTargetPosNode = theHeroTargetPosNode->down;
			if(!CPlayerInfo::CheckCollisionTarget())
			{
				vel.Set(0, -movementSpeed * 2, 0);
				currentState = KNOCKED_BACKING;

				heroAnimationDirection = UP;
				heroAnimationInvert = false;
				heroAnimationCounter = 0.0f;
			}
			else
			{
				theHeroTargetPosNode = theHeroCurrentPosNode;
			}
		}
		else if(AI_Pos.y < theHeroCurrentPosNode->pos.y)
		{
			theHeroTargetPosNode = theHeroTargetPosNode->up;
			if(!CPlayerInfo::CheckCollisionTarget())
			{
				vel.Set(0, movementSpeed * 2, 0);
				currentState = KNOCKED_BACKING;

				heroAnimationDirection = DOWN;
				heroAnimationInvert = false;
				heroAnimationCounter = 0.0f;
			}
			else
			{
				theHeroTargetPosNode = theHeroCurrentPosNode;
			}
		}
		else if(AI_Pos.x > theHeroCurrentPosNode->pos.x)
		{
			theHeroTargetPosNode = theHeroTargetPosNode->left;
			if(!CPlayerInfo::CheckCollisionTarget())
			{
				vel.Set(-movementSpeed * 2, 0, 0);
				currentState = KNOCKED_BACKING;

				heroAnimationDirection = RIGHT;
				heroAnimationInvert = false;
				heroAnimationCounter = 0.0f;
			}
			else
			{
				theHeroTargetPosNode = theHeroCurrentPosNode;
			}
		}
		else if(AI_Pos.x < theHeroCurrentPosNode->pos.x)
		{
			theHeroTargetPosNode = theHeroTargetPosNode->right;
			if(!CPlayerInfo::CheckCollisionTarget())
			{
				vel.Set(movementSpeed * 2, 0, 0);
				currentState = KNOCKED_BACKING;

				heroAnimationDirection = LEFT;
				heroAnimationInvert = true;
				heroAnimationCounter = 0.0f;
			}
			else
			{
				theHeroTargetPosNode = theHeroCurrentPosNode;
			}
		}
	}
	else
	{
		swap(theHeroTargetPosNode, theHeroCurrentPosNode);
		if(theHeroCurrentPosNode->up == theHeroTargetPosNode)
		{
			vel.Set(0, movementSpeed * 2, 0);

			heroAnimationDirection = DOWN;
			heroAnimationInvert = false;
			heroAnimationCounter = 0.0f;
		}
		else if(theHeroCurrentPosNode->down == theHeroTargetPosNode)
		{
			vel.Set(0, -movementSpeed * 2, 0);

			heroAnimationDirection = UP;
			heroAnimationInvert = false;
			heroAnimationCounter = 0.0f;
		}
		else if(theHeroCurrentPosNode->left == theHeroTargetPosNode)
		{
			vel.Set(-movementSpeed * 2, 0,0);

			heroAnimationDirection = RIGHT;
			heroAnimationInvert = false;
			heroAnimationCounter = 0.0f;
		}
		else if(theHeroCurrentPosNode->right == theHeroTargetPosNode)
		{
			vel.Set(movementSpeed * 2, 0,0);

			heroAnimationDirection = LEFT;
			heroAnimationInvert = true;
			heroAnimationCounter = 0.0f;
		}
		currentState = KNOCKED_BACKING;
	}
}


void CPlayerInfo::moving(float timeDiff)
{
	theHeroPosition += vel * timeDiff;
	if((theHeroPosition - theHeroCurrentPosNode->pos).Length() > (theHeroTargetPosNode->pos - theHeroCurrentPosNode->pos).Length())
	{
		theHeroPosition = theHeroTargetPosNode->pos;
		theHeroCurrentPosNode = theHeroTargetPosNode;
		currentState = NIL;
	}
}

void CPlayerInfo::moveAnimation(float timeDiff, Vector3 prevPos)
{
	if(theHeroPosition.y > prevPos.y)
	{
		heroAnimationDirection = UP;
		heroAnimationInvert = false;
		heroAnimationCounter += heroAnimationSpeed * timeDiff;
		if(heroAnimationCounter > backMeshes.size() - 1)
			heroAnimationCounter = 1.0f;
	}
	else if(theHeroPosition.y < prevPos.y)
	{
		heroAnimationDirection = DOWN;
		heroAnimationInvert = false;
		heroAnimationCounter += heroAnimationSpeed * timeDiff;
		if(heroAnimationCounter > frontMeshes.size() - 1)
			heroAnimationCounter = 1.0f;
	}
	else if(theHeroPosition.x > prevPos.x)
	{
		heroAnimationDirection = RIGHT;
		heroAnimationInvert = false;
		heroAnimationCounter += heroAnimationSpeed * timeDiff;
		if(heroAnimationCounter > sideMeshes.size() - 1)
			heroAnimationCounter = 0.0f;
	}
	else if(theHeroPosition.x < prevPos.x)
	{
		heroAnimationDirection = LEFT;
		heroAnimationInvert = true;
		heroAnimationCounter -= heroAnimationSpeed * timeDiff;
		if(heroAnimationCounter < 0.0f)
			heroAnimationCounter = sideMeshes.size() - 1;
	}
}


void CPlayerInfo::attackingEnabled()
{
	switch(heroAnimationDirection)
	{
	case UP:
		{
			theHeroTargetPosNode = theHeroTargetPosNode->up;
		}
		break;
	case DOWN:
		{
			theHeroTargetPosNode = theHeroTargetPosNode->down;
		}
		break;
	case LEFT:
		{
			theHeroTargetPosNode = theHeroTargetPosNode->left;
		}
		break;
	case RIGHT:
		{
			theHeroTargetPosNode = theHeroTargetPosNode->right;
		}
		break;
	}
	currentState = ATTACKING;
	this->heroAnimationCounter = 0.0f;
}

void CPlayerInfo::Attacking(float timeDiff, CAIManager* ai_manager, GameObjectFactory* go_manager)
{
	float PrevHeroAnimationCounter = heroAnimationCounter;
	heroAnimationCounter += heroAnimationSpeed * 2 * timeDiff;
	if(PrevHeroAnimationCounter <= (attackFrontMeshes.size() - 1) * 0.5 
		&& heroAnimationCounter >= (attackFrontMeshes.size() - 1) * 0.5)
	{
		for(int i = 0; i < ai_manager->enemiesList.size(); ++i)
		{
			if((ai_manager->enemiesList[i]->GetTargetPosNode() == theHeroCurrentPosNode
				&& ai_manager->enemiesList[i]->GetCurrentPosNode() == theHeroTargetPosNode)
				|| ai_manager->enemiesList[i]->GetCurrentPosNode() == theHeroTargetPosNode)
			{
				ai_manager->enemiesList[i]->SetPos(theHeroTargetPosNode->pos);
			}
		}
	}
	else if(heroAnimationCounter > attackFrontMeshes.size() - 1)
	{
		currentState = NIL;
		heroAnimationCounter = 0.0f;
		theHeroTargetPosNode = theHeroCurrentPosNode;
	}
}

bool CPlayerInfo::CheckCollisionTarget(void)
{
	switch(theHeroTargetPosNode->posType)
	{
	case CPosNode::NONE:
		return false;
	case CPosNode::HOLE:
		return false;
	case CPosNode::DOOR:
		return false;
	case CPosNode::WET_FLOOR:
		return false;
	case CPosNode::TIMING_DOOR:
		{
			ActiveGameObject* temp = dynamic_cast<ActiveGameObject*>(theHeroTargetPosNode->gameObject);
			if(temp->active)
				return false;
			else
				return true;
		}
	case CPosNode::LOCKED_DOOR:
		{
			ActiveGameObject* temp = dynamic_cast<ActiveGameObject*>(theHeroTargetPosNode->gameObject);
			if(temp->active)
				return false;
			else
				return true;
		}
	case CPosNode::ENEMY_INITIAL_POS:
		return false;
	case CPosNode::HERO_INIT_POS:
		return false;
	default:
		return true;
	}
}

bool CPlayerInfo::CheckCollisionCurrent(void)
{
	switch(theHeroCurrentPosNode->posType)
	{
	case CPosNode::NONE:
		return false;
	case CPosNode::ENEMY_INITIAL_POS:
		return false;
	case CPosNode::HERO_INIT_POS:
		return false;
	default:
		return true;
	}
}

void CPlayerInfo::CollisionResponseCurrent(void)
{
	switch(theHeroCurrentPosNode->gameObject->type)
	{
	case GameObject::HOLE:
		{
			//play fall animation or die
		}
		break;
	case GameObject::DOOR:
		{
			SetCurrentState(EXITING);
		}
		break;
	case GameObject::WET_FLOOR:
		{
			switch(heroAnimationDirection)
			{
			case UP:
				{
					theHeroTargetPosNode = theHeroTargetPosNode->up;
					vel.Set(0, movementSpeed, 0);
					currentState = MOVING;
				}
				break;
			case DOWN:
				{
					theHeroTargetPosNode = theHeroTargetPosNode->down;
					vel.Set(0, -movementSpeed, 0);
					currentState = MOVING;
				}
				break;
			case LEFT:
				{
					theHeroTargetPosNode = theHeroTargetPosNode->left;
					vel.Set(-movementSpeed, 0, 0);
					currentState = MOVING;
				}
				break;
			case RIGHT:
				{
					theHeroTargetPosNode = theHeroTargetPosNode->right;
					vel.Set(movementSpeed, 0, 0);
					currentState = MOVING;
				}
				break;
			}

			if(theHeroTargetPosNode->gameObject != NULL && theHeroTargetPosNode->gameObject->type > 0 && theHeroTargetPosNode->gameObject->type < GameObject::TOTAL && theHeroTargetPosNode->gameObject->type != GameObject::WET_FLOOR)
			{
				theHeroTargetPosNode = theHeroCurrentPosNode;
				currentState = NIL;
			}
			else
			{
				currentState = SLIDING;
				heroAnimationCounter = 0.0f;
			}
		}
		break;
	case GameObject::TIMING_DOOR:
		{
			ActiveGameObject* temp = dynamic_cast<ActiveGameObject*>(theHeroCurrentPosNode->gameObject);
			if(temp->active)
				SetCurrentState(EXITING);
		}
		break;
	case GameObject::LOCKED_DOOR:
		{
			ActiveGameObject* temp = dynamic_cast<ActiveGameObject*>(theHeroCurrentPosNode->gameObject);
			if(temp->active)
				SetCurrentState(EXITING);
		}
		break;
	case GameObject::HEALTH_PACK:
		{
			ActiveGameObject* temp = dynamic_cast<ActiveGameObject*>(theHeroCurrentPosNode->gameObject);
			if(temp->active /*&& health < 3*/)
			{
				//add player health
				temp->active = false;
			}
		}
		break;
	}
}