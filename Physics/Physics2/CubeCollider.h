#pragma once
#include "Collider.h"


class Transform;
class Entity;

class CubeCollider : public Collider
{



public:

	CubeCollider(std::shared_ptr<Entity> parent = nullptr);



	glm::vec3 m_BaseDimensions;
	glm::vec3 m_Dimensions;

};

