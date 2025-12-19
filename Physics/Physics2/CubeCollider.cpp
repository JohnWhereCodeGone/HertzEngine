#include "CubeCollider.h"
#include "../Entity/Entity.h"

CubeCollider::CubeCollider(std::shared_ptr<Entity> parent)
{
	m_BaseDimensions.x = 2.f;
	m_BaseDimensions.y = 2.f;
	m_BaseDimensions.z = 2.f;

	this->m_Dimensions = m_BaseDimensions;



	if (parent)
	{
		this->m_parent = parent;
		this->m_transform = parent->GetTransform();

	}
	else
	{
		this->m_transform = std::make_shared<Transform>();
	}

	this->m_isSatellite = false;
	this->m_center = m_transform->GetPos();
	this->m_velocity = glm::vec3(0.f);
	this->m_mass = 2.f;
	this->m_bHasGravity = true;
	this->m_type = ColliderType::Cube;
	this->m_isKinematic = false;
	

}
