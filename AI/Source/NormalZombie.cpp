#include "NormalZombie.h"


CNormalZombie::CNormalZombie(void)
{
}

CNormalZombie::~CNormalZombie(void)
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

void CNormalZombie::Init(CMap *map)
{
	movementSpeed = 200.f;
	zombie_type = NORMAL;
	maxRangeToDetect = map->GetTileSize() * 3;
	zombieAnimationCounter = 0.0f;
	zombieAnimationInvert = false;
}

// Reset this class instance
void CNormalZombie::Reset(void)
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