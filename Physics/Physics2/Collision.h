#pragma once
#include "Collider.h"



struct Collision
{

	bool m_hasCollided = false;
	Collider* m_col1;
	Collider* m_col2;


	glm::vec3 m_normal;
	glm::vec3 m_point;

};

