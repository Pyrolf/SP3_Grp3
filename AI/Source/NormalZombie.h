#pragma once
#include "Zombie.h"

class CNormalZombie
	: public CZombie
{
public:
	CNormalZombie(void);
	virtual ~CNormalZombie(void);

	virtual void Init(CMap *map);

	// Reset this class instance
	virtual void Reset(void);
};