#include "Transform.h"
#include "../glm/glm.hpp"
#include "Camera.h"






Transform::Transform()
{
	this->m_vPos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vScale = glm::vec3(1.0f, 1.0f, 1.0f);
	this->m_model = glm::mat4(1.0f);
	this->m_VelocityDecayRate = 0.95f;
	this->m_vVelocity = glm::vec3(0.0f);
	this->m_shader = {};

	this->m_stellartype = UNSPECIFIED;
}

Transform::Transform(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale, std::shared_ptr<Shader> shader)
{
	this->m_vPos = pos;
	this->m_vRotation = rotation;
	this->m_vScale = scale;
	this->m_model = glm::mat4(1.f);
	this->m_VelocityDecayRate = 0.99f;
	this->m_vVelocity = glm::vec3(0.0f);
	this->m_visualPos = glm::vec3(0.0f);
	
	if (shader)
	{
		this->m_shader = shader;
	}
	else
		this->m_shader = nullptr;
	
}
glm::dvec3& Transform::GetPos()
{
	return this->m_vPos;
}

glm::dvec3& Transform::GetScale()
{
	return this->m_vScale;
}

glm::vec3& Transform::GetRot()
{

	this->m_vRotation.x = (int)this->m_vRotation.x % 360;
	this->m_vRotation.y = (int)this->m_vRotation.y % 360;
	this->m_vRotation.z = (int)this->m_vRotation.z % 360;

	return this->m_vRotation;
}

glm::vec3& Transform::GetVelocity()
{
	return this->m_vVelocity;
}

// 3 types of light, point point light, dir light, spotlight <- structure this into a class that handles all shaders.
// then mip settings, UI add functions from Transform to update pos, rotation, scale.
void Transform::SetPos(const glm::dvec3& newPos)
{
	


	this->m_vPos = newPos;
}

void Transform::SetRot(const glm::vec3& newRot)
{
	glm::vec3 temp = newRot;

	temp.x = (int)temp.x % 360;
	temp.y = (int)temp.y % 360;
	temp.z = (int)temp.z % 360;

	this->m_vRotation = temp;
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
	transmat = glm::translate(transmat, (glm::vec3)m_vPos);
	transmat = glm::rotate(transmat, glm::radians(m_vRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

	transmat = glm::rotate(transmat, glm::radians(m_vRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

	transmat = glm::rotate(transmat, glm::radians(m_vRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transmat = glm::scale(transmat, (glm::vec3)m_vScale);



	shader->Use();
	shader->setMat4("model", transmat);
	this->m_model = transmat;


}

void Transform::UpdateModelPlanetary(std::shared_ptr<Shader> shader, std::shared_ptr<Camera> cam)
{

	if (!shader)
		return;

	glm::dvec3 floatingOriginPos = glm::dvec3(0);

	glm::mat4 transmat = glm::mat4(1.0f);
	glm::dvec3 appliedPosition = m_vPos;
	glm::vec3 renderScale = m_vScale * SCALE;
	
	switch (m_stellartype)
	{
	case(UNSPECIFIED):
		renderScale *= 1.0f;
		break;

	case(STAR):
		renderScale *= 1.0f;   //sun is size 10.
		break;

	case(PLANET):
		renderScale *= 5.0f;
		break;


	}




	if (cam)
	{
		appliedPosition = (m_vPos - cam->vPos) * SCALE;
	}
	else
	{
		appliedPosition = m_vPos * SCALE;
	}

	transmat = glm::translate(transmat, (glm::vec3)appliedPosition);
	glm::mat4 rotMat = glm::mat4_cast(m_rotationQuat);
	transmat *= rotMat;
	transmat = glm::scale(transmat, renderScale);



	shader->Use();
	shader->setMat4("model", transmat);
	this->m_visualPos = appliedPosition;
	this->m_model = transmat;

}

glm::vec3& Transform::GetVisualPos()
{
	return this->m_visualPos;
}

void Transform::Move(float deltaTime)
{
	this->m_vPos += this->m_vVelocity * deltaTime;
	this->m_vVelocity *= m_VelocityDecayRate;
}

const glm::mat4& Transform::GetModel()
{
	return this->m_model;
}
