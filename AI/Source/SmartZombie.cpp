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
	zombie_type = SMART;
	maxRangeToDetect = map->GetTileSize() * 4;
	zombieAnimationCounter = 0.0f;
	zombieAnimationInvert = false;
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

	movementSpeed = 200.f;
	zombie_type = ZOMBIE_TYPE::NORMAL;
}