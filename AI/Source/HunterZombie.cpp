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
	movementSpeed = 350.f;
	animationSpeed = 40;
	zombie_type = HUNTER;
	maxRangeToDetect = map->GetTileSize() * 3;
	zombieAnimationCounter = 0.0f;
	zombieAnimationInvert = false;
	health = 5;
}

// Reset this class instance
void CHunterZombie::Reset(void)
{
	theZombiePosition = theZombieInitialPosNode->pos;
	theZombieCurrentPosNode = theZombieInitialPosNode;
	theZombieTargetPosNode = theZombieCurrentPosNode;
	
	currentMode = NIL;

	zombieAnimationDirection = DOWN;
	zombieAnimationCounter = 0.0f;
	zombieAnimationInvert = false;

	active = true;
	health = 5;
}