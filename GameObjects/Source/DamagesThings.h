#pragma once
#include "Killable.h"

class DamagesThings
{
public:
	DamagesThings();
	~DamagesThings();

	void DoDamageTo(Killable* theKill);

protected:
	float damage;
};

