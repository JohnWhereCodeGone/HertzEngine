#include "CubeCollider.h"
#include "../Entity/Entity.h"

CubeCollider::CubeCollider(std::shared_ptr<Entity> parent)
{
	m_Dimensions.x = 2.f;
	m_Dimensions.y = 2.f;
	m_Dimensions.z = 2.f;





	if (parent)
	{
		this->m_parent = parent;
		this->transformClass = parent->GetTransform();

	}
	else
	{
		this->transformClass = std::make_shared<Transform>();
	}


	this->m_center = transformClass->GetPos();
	this->velocity = glm::vec3(0);
	this->mass = 1.f;
	this->m_bHasGravity = true;
	this->m_type = ColliderType::Cube;
	

}
