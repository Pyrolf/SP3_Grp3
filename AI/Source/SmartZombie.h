#pragma once
#include "Zombie.h"

class CSmartZombie
	: public CZombie
{
public:
	CSmartZombie(void);
	virtual ~CSmartZombie(void);

	virtual void Init(CMap *map);

	// Reset this class instance
	virtual void Reset(void);
};