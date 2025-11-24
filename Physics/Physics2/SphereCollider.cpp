#include "SphereCollider.h"
#include "../Entity/Entity.h"

SphereCollider::SphereCollider(std::shared_ptr<Entity> parent)
{

	this->m_bHasGravity = true;
	
	if (parent)
	{
		this->transformClass = parent->GetTransform();
	}
	else
	{
		this->transformClass = std::make_shared<Transform>();
	}
	this->m_center = transformClass->GetPos();
	this->m_Radius = 1.f;

	this->velocity = glm::vec3(0);
	this->mass = 1.f;
	this->m_bHasGravity = true;

}
