#include "HunterZombie.h"


CHunterZombie::CHunterZombie(void)
{
}

CHunterZombie::~CHunterZombie(void)
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

void CHunterZombie::Init(CMap *map)
{
	movementSpeed = 400.f;
	zombie_type = HUNTER;
	maxRangeToDetect = map->GetTileSize() * 5;
	zombieAnimationCounter = 0.0f;
	zombieAnimationInvert = false;
}

// Reset this class instance
void CHunterZombie::Reset(void)
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