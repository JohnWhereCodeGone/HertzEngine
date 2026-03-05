#pragma once
#include "Collider.h"
#include "../Transform.h"
#include <queue>
#include "../Shaders/HertzShader.h"
#include  "../Mesh/Trail.h"


class Trail;

class SphereCollider : public Collider
{

public:

	SphereCollider(std::shared_ptr<Entity> parent = nullptr);



	double	m_Radius;
	float	m_BaseRadius;
	std::unique_ptr<Trail>	m_trail;

};

