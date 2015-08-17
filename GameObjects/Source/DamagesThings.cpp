#include "DamagesThings.h"
#include "Killable.h"

DamagesThings::DamagesThings()
{
}

DamagesThings::~DamagesThings()
{
}

void DamagesThings::DoDamageTo(Killable* theKill)
{
	theKill->GetDamaged(damage);
}