#pragma once
#include "../glm/glm.hpp"
#include <iostream>

class Collider;




class Raycast
{
public:

	Raycast(const glm::vec3& inOrigin, const glm::vec3& inDirection)
	{
		m_origin	= inOrigin;
		m_direction = inDirection;
	};


	glm::vec3 m_origin;
	glm::vec3 m_direction;
};
struct RayHit
{

	RayHit() {};

	RayHit(glm::vec3 aPoint, std::shared_ptr<Collider> inCollider, float distance)
	{
		m_point		= aPoint;
		m_collider	= inCollider;
		m_distance	= distance;
	}

	glm::vec3					m_point;
	std::shared_ptr<Collider>	m_collider;
	float						m_distance;

};

