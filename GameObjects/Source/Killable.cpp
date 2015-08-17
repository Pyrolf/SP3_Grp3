#include "Killable.h"

Killable::Killable()
	:
health(0)
{
}

Killable::~Killable()
{
}

const float& Killable::GetHealth()
{
	return health;
}

void Killable::GetDamaged(const float& damage)
{
	health -= damage;
}

bool Killable::IsDead()
{
	return health <= 0;
}