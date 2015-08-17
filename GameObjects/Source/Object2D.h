#pragma once
#include "Vector3.h"

class Object2D
{
public:
	Object2D();
	virtual ~Object2D();
	virtual void Update(const double& deltaTime) = 0;
	virtual void DoCollisionWith(Object2D* obj) = 0;

	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float rotationalVelocity;
	float rotationalAcceleration;

	bool active;

protected:
	void UpdatePosition(const double& deltaTime);
	void UpdateVelocity(const double& deltaTime);
};

