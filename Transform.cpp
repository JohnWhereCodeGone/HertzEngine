#include "Transform.h"


Transform::Transform()
{
	this->m_vPos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vScale = glm::vec3(1.0f, 1.0f, 1.0f);
	this->m_model = glm::mat4(1.0f);
	this->m_VelocityDecayRate = 0.95f;
	this->m_vVelocity = glm::vec3(0.0f);
	this->m_shader = {};
}

Transform::Transform(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale, std::shared_ptr<Shader> shader)
{
	this->m_vPos = pos;
	this->m_vRotation = rotation;
	this->m_vScale = scale;
	this->m_model = glm::mat4(1.f);
	this->m_VelocityDecayRate = 0.99f;
	this->m_vVelocity = glm::vec3(0.0f);
	
	if (shader)
	{
		this->m_shader = shader;
	}
	else
		this->m_shader = nullptr;
	
}
glm::vec3& Transform::GetPos()
{
	return this->m_vPos;
}

glm::vec3& Transform::GetScale()
{
	return this->m_vScale;
}

glm::vec3& Transform::GetRot()
{
	return this->m_vRotation;
}

// 3 types of light, point point light, dir light, spotlight <- structure this into a class that handles all shaders.
// then mip settings, UI add functions from Transform to update pos, rotation, scale.
void Transform::SetPos(const glm::vec3& newPos)
{
	this->m_vPos = newPos;
}

void Transform::SetRot(const glm::vec3& newRot)
{
	this->m_vRotation = newRot;
}

void Transform::SetScale(const glm::vec3& newScale)
{
	this->m_vScale = newScale;
}

void Transform::AddVelocity(const glm::vec3& addedVelocity)
{
	this->m_vVelocity += addedVelocity;
}

void Transform::AddVelocity(float x, float y, float z)
{
	this->m_vVelocity.x += x;
	this->m_vVelocity.y += y;
	this->m_vVelocity.z += z;
}

void Transform::UpdateModel(std::shared_ptr<Shader> shader)
{
	if (!shader)
		return;
	
	glm::mat4 transmat = glm::mat4(1.0f);
	

	// use quaternions for rotation to avoid 'gimbal lock' - lest you be branded a heretic.
	transmat = glm::translate(transmat, m_vPos);
	transmat = glm::rotate(transmat, glm::radians(m_vRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transmat = glm::rotate(transmat, glm::radians(m_vRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transmat = glm::rotate(transmat, glm::radians(m_vRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transmat = glm::scale(transmat, m_vScale);

	shader->Use();
	shader->setMat4("model", transmat);
	this->m_model = transmat;


}

void Transform::Move(float deltaTime)
{
	this->m_vPos += this->m_vVelocity * deltaTime;
	this->m_vVelocity *= m_VelocityDecayRate;
}
