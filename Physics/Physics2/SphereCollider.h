#pragma once
#include "Collider.h"
#include "../Transform.h"
#include <queue>
#include "../Shaders/HertzShader.h"



class SphereCollider : public Collider
{

public:

	SphereCollider(std::shared_ptr<Entity> parent = nullptr);



	double	m_Radius;
	float	m_BaseRadius;

};

