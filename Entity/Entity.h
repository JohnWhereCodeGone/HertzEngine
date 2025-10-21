#pragma once
#include "../Objects/VirtualObject.h"

class Entity : public VirtualObject
{
public:

	Entity();

	void Update(float DeltaTime);
	float GetVelocity();


};

