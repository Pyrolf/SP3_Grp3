#include "SmartZombie.h"


CSmartZombie::CSmartZombie(void)
{
}

CSmartZombie::~CSmartZombie(void)
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

void CSmartZombie::Init(CMap *map)
{
	movementSpeed = 300.f;
	animationSpeed = 30;
	zombie_type = SMART;
	maxRangeToDetect = map->GetTileSize() * 3;
	zombieAnimationCounter = 0.0f;
	zombieAnimationInvert = false;
	health = 4;
}

// Reset this class instance
void CSmartZombie::Reset(void)
{
	theZombiePosition = theZombieInitialPosNode->pos;
	theZombieCurrentPosNode = theZombieInitialPosNode;
	theZombieTargetPosNode = theZombieCurrentPosNode;

	currentMode = RETURN;

	zombieAnimationDirection = DOWN;
	zombieAnimationCounter = 0.0f;
	zombieAnimationInvert = false;

	active = true;
	health = 4;
}