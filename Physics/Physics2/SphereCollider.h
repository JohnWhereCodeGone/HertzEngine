#pragma once
#include "Collider.h"
#include "../Transform.h"


class SphereCollider : public Collider
{

public:

	SphereCollider(std::shared_ptr<Entity> parent = nullptr);

	float m_Radius;

	std::shared_ptr<Transform> transformClass;
};

