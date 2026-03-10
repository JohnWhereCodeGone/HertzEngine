#include "Transform.h"
#include "../glm/glm.hpp"
#include "Camera.h"
#include "Entity/Entity.h"





Transform::Transform()
{
	this->m_vPos				= glm::dvec3(0.0f, 0.0f, 0.0f);
	this->m_vRotation			= glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vScale				= glm::dvec3(1.0f, 1.0f, 1.0f);
	this->m_model				= glm::mat4(1.0f);
	this->m_VelocityDecayRate	= 0.95f;
	this->m_shader = {};
	this->m_vPosError			= glm::dvec3(0.0);
	this->m_prevLocalPos		= glm::dvec3(0.0);
	this->m_interpolatedLocalPos = glm::dvec3(0.0);
	this->m_localPos		= glm::dvec3(0.0);

	this->m_stellartype = UNSPECIFIED;
}

Transform::Transform(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale, std::shared_ptr<Shader> shader)
{
	this->m_vPos				= glm::dvec3(0.0f, 0.0f, 0.0f);
	this->m_vRotation			= glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_vScale				= glm::dvec3(1.0f, 1.0f, 1.0f);
	this->m_model				= glm::mat4(1.0f);
	this->m_VelocityDecayRate	= 0.95f;
	this->m_shader = {};
	this->m_vPosError			= glm::dvec3(0.0);
	this->m_prevLocalPos		= glm::dvec3(0.0);
	this->m_interpolatedLocalPos = glm::dvec3(0.0);
	this->m_localPos		= glm::dvec3(0.0);

	this->m_stellartype = UNSPECIFIED;

	if (shader)
	{
		this->m_shader = shader;
	}
	else
		this->m_shader = nullptr;
	
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



// 3 types of light, point point light, dir light, spotlight <- structure this into a class that handles all shaders.
// then mip settings, UI add functions from Transform to update pos, rotation, scale.
void Transform::SetPos(const glm::dvec3& newPos)
{
	if (glm::any(glm::isnan(newPos)) || glm::any(glm::isinf(newPos))) {

		__debugbreak();
	}

	this->m_prevLocalPos = m_localPos;
	this->m_localPos = newPos;
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




void Transform::UpdateModel(std::shared_ptr<Shader> shader)
{
	if (!shader)
		return;
	
	
	glm::mat4 transmat = glm::mat4(1.0f);

	// use quaternions for rotation to avoid 'gimbal lock' - lest you be branded a heretic.
	transmat = glm::translate(transmat, (glm::vec3)m_localPos);
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
	

	if (!shader) return;

	glm::mat4 transmat = glm::mat4(1.0f);
	glm::dvec3 appliedPosition = m_localPos;

	glm::vec3 renderScale = m_vScale * RENDER_SCALE;

	switch (m_stellartype)
	{
	case(UNSPECIFIED): renderScale *= 1.0f; 
		break;
	case(STAR):        renderScale *= 2.0f; 
		break;
	case(PLANET):      renderScale *= 2.0f; 
		break; 
	}

	if (cam)
	{
		appliedPosition = (m_interpolatedLocalPos - cam->vPos) * RENDER_SCALE;
	}
	else
	{
		appliedPosition = m_interpolatedLocalPos * RENDER_SCALE;
	}

	// Now it is safe to cast to a 32-bit float!
	transmat = glm::translate(transmat, (glm::vec3)appliedPosition);
	glm::mat4 rotMat = glm::mat4_cast(m_rotationQuat);
	transmat *= rotMat;
	transmat = glm::scale(transmat, renderScale);

	shader->Use();
	shader->setMat4("model", transmat);
	this->m_visualPos = appliedPosition;
	this->m_model = transmat;
	cam->CameraUpdate();

}

glm::dvec3& Transform::GetVisualPos()
{
	return this->m_visualPos;
}

double Transform::GetRenderScale()
{
	return RENDER_SCALE;
}



const glm::mat4& Transform::GetModel()
{ 
	return this->m_model;
}

void Transform::AddPosKahan(const glm::dvec3& offset)
{
	if (glm::any(glm::isnan(offset)) || glm::any(glm::isinf(offset))) {
		return;
	}
	glm::dvec3 y = offset - m_vPosError; //where error is corrected
	
	

	glm::dvec3 t = m_localPos + y; //where error is created

	m_vPosError = (t - m_localPos) - y; //where error is recovered

	m_localPos = t;

	

}

glm::dvec3 Transform::GetWorldPos() const
{
	if (m_parent)
	{
		return this->m_localPos + m_parent->GetTransform()->GetWorldPos();
	}
	else
	{
		return this->m_localPos;

	}
}

glm::dvec3 Transform::GetLocalPos() const
{
	return this->m_localPos;
}

glm::dvec3& Transform::GetPos()
{
	return this->m_localPos;
}