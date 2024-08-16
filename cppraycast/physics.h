#ifndef  THEPHYSICS_H
#define THEPHYSICS_H
#include <iostream>

class thePhysics
{
public:
	thePhysics() = default;

	void integrate(float& deltatime);
	void physicsconstants();
	void physicsobjectlift(float& deltatime, bool& isfalling);
	void physicssetup(float& lift);

public:
	bool isfalling;
	bool iscaught;
	float gravity;
	int pixels_per_meter;;
	float* pos = nullptr;
	float vel;
	float accelerate;
	float deltatime;
};

#endif // ! PHYSICS_H


