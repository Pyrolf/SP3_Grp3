#pragma once
#include "Zombie.h"

class CTankZombie
	: public CZombie
{
public:
	CTankZombie(void);
	virtual ~CTankZombie(void);

	virtual void Init(CMap *map);

	// Reset this class instance
	virtual void Reset(void);
};