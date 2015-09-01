#include "TankZombie.h"


CTankZombie::CTankZombie(void)
{
}

CTankZombie::~CTankZombie(void)
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

void CTankZombie::Init(CMap *map)
{
	movementSpeed = 100.f;
	animationSpeed = 10;
	zombie_type = TANK;
	maxRangeToDetect = map->GetTileSize() * 4;
	zombieAnimationCounter = 0.0f;
	zombieAnimationInvert = false;
	health = 10;
}

// Reset this class instance
void CTankZombie::Reset(void)
{
	theZombiePosition = theZombieInitialPosNode->pos;
	theZombieCurrentPosNode = theZombieInitialPosNode;
	theZombieTargetPosNode = theZombieCurrentPosNode;

	currentMode = RETURN;

	zombieAnimationDirection = DOWN;
	zombieAnimationCounter = 0.0f;
	zombieAnimationInvert = false;

	active = true;
	health = 10;
}