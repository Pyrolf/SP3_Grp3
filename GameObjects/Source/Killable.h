#pragma once

class Killable
{
public:
	Killable();
	~Killable();
	const float& GetHealth();
	void GetDamaged(const float& damage);
	bool IsDead();

protected:
	float health;
};

