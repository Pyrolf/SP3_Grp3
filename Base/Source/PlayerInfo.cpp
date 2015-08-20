#include "PlayerInfo.h"
#include <iostream>

static float GRAVITY = 3000.f;

CPlayerInfo::CPlayerInfo(void)
	: theHeroPosition(Vector3(0, 0, 0))
	, theHeroInitialPosition(Vector3(0, 0, 0))
	, theHeroTargetPosition(Vector3(0, 0, 0))
	, movementSpeed(200.0f)
	, currentState(PLAYING)
	, timeElasped(0.f)
	, heroAnimationDirection(DOWN)
	, heroAnimationCounter(0.0f)
	, heroAnimationInvert(false)
	, health(3)
	, deathRotate(0)
	, isKnockingBack(false)
{
}


CPlayerInfo::~CPlayerInfo(void)
{
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

// Set initial position x of the player
void CPlayerInfo::SetInitialPos_x(float pos_x)
{
	theHeroInitialPosition.x = pos_x;
}

// Set initial position y of the player
void CPlayerInfo::SetInitialPos_y(float pos_y)
{
	theHeroInitialPosition.y = pos_y;
}

// Set target position x of the player
void CPlayerInfo::SetTargetPos_x(float pos_x)
{
	theHeroTargetPosition.x = pos_x;
}

// Set target position y of the player
void CPlayerInfo::SetTargetPos_y(float pos_y)
{
	theHeroTargetPosition.y = pos_y;
}

/********************************************************************************
Hero Move Up Down
********************************************************************************/
void CPlayerInfo::MoveUpDown(const bool mode, const float timeDiff, CMap* m_cMap)
{
	if (mode)
	{
		theHeroTargetPosition.y += m_cMap->GetTileSize();
	}
	else
	{
		theHeroTargetPosition.y -= m_cMap->GetTileSize();
	}
}

/********************************************************************************
Hero Move Left Right
********************************************************************************/
void CPlayerInfo::MoveLeftRight(const bool mode, const float timeDiff, CMap* m_cMap)
{
	if (mode)
	{
		theHeroTargetPosition.x -= m_cMap->GetTileSize();
	}
	else
	{
		theHeroTargetPosition.x += m_cMap->GetTileSize();
	}
}

// Get position x of the player
float CPlayerInfo::GetPos_x(void)
{
	return theHeroPosition.x;
}

// Get position y of the player
float CPlayerInfo::GetPos_y(void)
{
	return theHeroPosition.y;
}

// Get target position x of the player
float CPlayerInfo::GetTargetPos_x(void)
{
	return theHeroTargetPosition.x;
}

// Get target position y of the player
float CPlayerInfo::GetTargetPos_y(void)
{
	return theHeroTargetPosition.y;
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

// Set Movement Speed of the player
void CPlayerInfo::SetMovementSpeed(float movementSpeed)
{
	this->movementSpeed = movementSpeed;
}

// Get Movement Speed of the player
float CPlayerInfo::GetMovementSpeed(void)
{
	return movementSpeed;
}

/********************************************************************************
Hero Update
********************************************************************************/
void CPlayerInfo::HeroUpdate(CMap* m_cMap, float timeDiff)
{
	// Update Hero's info
	if(isKnockingBack)
	{
		knockingBack(timeDiff);
	}
	else if(theHeroTargetPosition != theHeroPosition)
	{
		Vector3 HeroPrevPos = theHeroPosition;
		theHeroPosition += (theHeroTargetPosition - theHeroPosition).Normalized() * movementSpeed * timeDiff;

		if(theHeroTargetPosition.y > HeroPrevPos.y)
		{
			heroAnimationDirection = UP;
			heroAnimationInvert = false;
			heroAnimationCounter += 30 * timeDiff;
			if(heroAnimationCounter > 8.0f)
				heroAnimationCounter = 1.0f;

			if(theHeroTargetPosition.y < theHeroPosition.y)
				theHeroPosition.y = theHeroTargetPosition.y;
		}
		else if(theHeroTargetPosition.y < HeroPrevPos.y)
		{
			heroAnimationDirection = DOWN;
			heroAnimationInvert = false;
			heroAnimationCounter += 30 * timeDiff;
			if(heroAnimationCounter > 8.0f)
				heroAnimationCounter = 1.0f;

			if(theHeroTargetPosition.y > theHeroPosition.y)
				theHeroPosition.y = theHeroTargetPosition.y;
		}
		else if(theHeroTargetPosition.x > HeroPrevPos.x)
		{
			heroAnimationDirection = RIGHT;
			heroAnimationInvert = false;
			heroAnimationCounter += 15 * timeDiff;
			if(heroAnimationCounter > 8.0f)
				heroAnimationCounter = 0.0f;

			if(theHeroTargetPosition.x < theHeroPosition.x)
				theHeroPosition.x = theHeroTargetPosition.x;
		}
		else if(theHeroTargetPosition.x < HeroPrevPos.x)
		{
			heroAnimationDirection = LEFT;
			heroAnimationInvert = true;
			heroAnimationCounter -= 15 * timeDiff;
			if(heroAnimationCounter < 0.0f)
				heroAnimationCounter = 8.0f;

			if(theHeroTargetPosition.x > theHeroPosition.x)
				theHeroPosition.x = theHeroTargetPosition.x;
		}
	}
}

void CPlayerInfo::Reset(void)
{
	theHeroPosition = theHeroInitialPosition;
	theHeroTargetPosition = theHeroPosition;

	currentState = CPlayerInfo::PLAYING;

	timeElasped = 0.f;

	heroAnimationDirection = DOWN;
	heroAnimationCounter = 0.0f;
	heroAnimationInvert = false;

	health = 3;

	deathRotate = 0;

	isKnockingBack = false;
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

// Set DeathRotate of the player
void CPlayerInfo::SetDeathRotate(float deathRotate)
{
	this->deathRotate = deathRotate;
}

// Get Death Rotate of the player
float CPlayerInfo::GetDeathRotate(void)
{
	return deathRotate;
}

void CPlayerInfo::knockBackEnabled(Vector3 knockBackPos)
{
	this->knockBackPos = knockBackPos;
	this->isKnockingBack = true;
}

void CPlayerInfo::knockingBack(float timeDiff)
{
	Vector3 HeroPrevPos = theHeroPosition;
	theHeroPosition += (knockBackPos - theHeroPosition).Normalized() * movementSpeed * 2 * timeDiff;

	if(knockBackPos.x > HeroPrevPos.x && knockBackPos.x < theHeroPosition.x)
	{
		knockBackPos.x = theHeroPosition.x;
	}
	else if(knockBackPos.x < HeroPrevPos.x && knockBackPos.x > theHeroPosition.x)
	{
		knockBackPos.x = theHeroPosition.x;
	}
	if(knockBackPos.y > HeroPrevPos.y && knockBackPos.y < theHeroPosition.y)
	{
		knockBackPos.y = theHeroPosition.y;
	}
	else if(knockBackPos.y < HeroPrevPos.y && knockBackPos.y > theHeroPosition.y)
	{
		knockBackPos.y = theHeroPosition.y;
	}
	if(theHeroPosition == knockBackPos)
	{
		this->isKnockingBack = false;
	}
}

bool CPlayerInfo::GetIsKnockingBack()
{
	return isKnockingBack;
}