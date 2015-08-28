#pragma once
#include "Zombie.h"

class CHunterZombie
	: public CZombie
{
public:
	CHunterZombie(void);
	virtual ~CHunterZombie(void);

	virtual void Init(CMap *map);

	// Reset this class instance
	virtual void Reset(void);
};