#pragma once
#include "../glm/glm.hpp"
#include "iostream"
#include "../Transform.h"

enum ColliderType
{
	Sphere,
	Cube
};


class Entity;

class Collider
{
public:	
	
	virtual ~Collider() {}
	
	template<typename T>
	bool isOf() { return (dynamic_cast<T*>(this) != nullptr); };

	std::shared_ptr<Transform>		m_transform;
	glm::vec3						m_center;
									
	bool							m_bHasGravity;
	glm::vec3						m_velocity;
	float							m_mass;
	ColliderType					m_type;
	std::shared_ptr<Entity>			m_parent;
	bool							m_isKinematic;



};

