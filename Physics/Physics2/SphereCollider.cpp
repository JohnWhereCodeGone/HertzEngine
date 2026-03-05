#include "SphereCollider.h"
#include "../Entity/Entity.h"
#include "../Mesh/Trail.h"



SphereCollider::SphereCollider(std::shared_ptr<Entity> parent)
{

	this->m_bHasGravity = true;
	
	if (parent)
	{
		this->m_transform = parent->GetTransform();
		this->m_parent = parent;
	}
	else
	{
		this->m_transform = std::make_shared<Transform>();
	}
	this->m_center = m_transform->GetPos();
	
	this->m_BaseRadius = 1.f;
	this->m_Radius = m_BaseRadius;

	this->m_force = glm::dvec3(0);
	this->m_nextAcceleration = glm::dvec3(0);
	this->m_isSatellite = true;
	this->m_acceleration = glm::dvec3(0);
	this->m_velocity = glm::dvec3(0);
	this->m_mass = 10000000;
	this->m_bHasGravity = true;
	this->m_type = ColliderType::Sphere;
	this->m_isKinematic = false;
	this->m_trail = std::make_unique<Trail>(m_transform);

	//next -> Fix Trail Class -> Add a position update to the physics loo0p. Then, create a function in the physics engine that simply renders. Call that function after position updates in the hertz engine.
	// Finally, in main, check the bool to enable updating for the trails. Add a simple per/entity color thingie. Look into basic trail styles.
	
	// Then, finish off the report, hand in the assignment before 1pm meeting with Sergei.
	



}


