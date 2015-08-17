#include "Ship2D.h"
#include "Bullet2DFactory.h"

Ship2D::Ship2D(Factory* factory)
{
	health = 100;
	velocity.Set(1,1,1);
	this->factory = factory;
	Bullet2DFactory* isBulletFactory = dynamic_cast<Bullet2DFactory*>(factory);

	if(!isBulletFactory)
	{
		throw;
	}
}

Ship2D::~Ship2D()
{
}
