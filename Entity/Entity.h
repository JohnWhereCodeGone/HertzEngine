#pragma once
#include "../Objects/VirtualObject.h"

class Entity : public VirtualObject
{
	using TexturePtr = std::shared_ptr<HertzTexture>;

public:

	Entity();

	void Update(float DeltaTime);
	float GetVelocity();

	

};

