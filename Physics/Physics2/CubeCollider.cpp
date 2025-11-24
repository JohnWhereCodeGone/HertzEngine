#include "CubeCollider.h"
#include "../Entity/Entity.h"

CubeCollider::CubeCollider(std::shared_ptr<Entity> parent)
{
	m_Dimensions.x = 1.f;
	m_Dimensions.y = 1.f;
	m_Dimensions.z = 1.f;



	if (parent)
	{
		this->m_parent = parent;
		this->transformClass = parent->GetTransform();

	}
	else
	{
		this->transformClass = std::make_shared<Transform>();
	}

	

}
