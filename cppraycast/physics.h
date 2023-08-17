#ifndef PHYSICS_H
#define PHYSICS_H
#include "Vec2.h"

struct PhysicObject
{
	float* tophalf;
	float* bottomhalf;
	float* floor;
	float acclerate;
	float velocity;
	float mass;
	float deltatime;

	void integrate();
	void physicssetup(float& tophalf, float& bottomhalf, float& floor);
	void physicsdisplay();
};

extern bool islifting;

#endif // PHYSICS_H


