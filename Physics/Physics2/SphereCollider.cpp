#include "SphereCollider.h"
#include "../Entity/Entity.h"

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

	this->m_trail = std::make_shared<Trail>();
	this->m_trail->Init();


}


void Trail::Init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

}

void Trail::UpdateBuffer()
{
	verticies.clear();
	verticies.reserve(points.size());
	for (const auto& point : points)
	{
		verticies.push_back((glm::vec3)point);
	}
}

void Trail::Draw()
{

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(glm::vec3), verticies.data(), GL_DYNAMIC_DRAW);

	glDrawArrays(GL_LINE_STRIP, 0, verticies.size());

	glBindVertexArray(0);

}
