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
	animationSpeed = 20;
	zombie_type = NORMAL;
	maxRangeToDetect = map->GetTileSize() * 2;
	zombieAnimationCounter = 0.0f;
	zombieAnimationInvert = false;
	health = 3;
}

// Reset this class instance
void CNormalZombie::Reset(void)
{
	theZombiePosition = theZombieInitialPosNode->pos;
	theZombieCurrentPosNode = theZombieInitialPosNode;
	theZombieTargetPosNode = theZombieCurrentPosNode;

	currentMode = NIL;

	zombieAnimationDirection = DOWN;
	zombieAnimationCounter = 0.0f;
	zombieAnimationInvert = false;

	active = true;
	health = 3;
}