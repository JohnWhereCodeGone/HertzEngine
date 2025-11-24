#pragma once
#include "../glm/glm.hpp"
#include "iostream"



class Entity;

class Collider
{
public:	
	
	virtual ~Collider() {}
	
	template<typename T>
	bool isOf() { return (dynamic_cast<T*>(this) != nullptr); };

	glm::mat4				m_transform;
	glm::vec3				m_center;
							
	bool					m_bHasGravity;
	glm::vec3				velocity;
	float					mass;

	std::shared_ptr<Entity> m_parent;



};

