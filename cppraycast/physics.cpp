#include "physics.h"


bool islifting = false;

void PhysicObject::integrate()
{
	velocity += acclerate * deltatime;
	*tophalf += velocity * deltatime;
	*bottomhalf += velocity * deltatime;
}

void PhysicObject::physicssetup(float& tophalf, float& bottomhalf, float& floor)
{
	this->tophalf = &tophalf;
	this->bottomhalf = &bottomhalf;
	this->floor = &floor;
}

void PhysicObject::physicsdisplay()
{
	acclerate = 9.8f * 50;

	integrate();

	if (bottomhalf >= floor)
	{
		bottomhalf = floor;
		velocity *= -0.9f;
	}
}
