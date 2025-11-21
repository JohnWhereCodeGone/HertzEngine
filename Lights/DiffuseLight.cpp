#include "DiffuseLight.h"





DiffuseLight::DiffuseLight()
{

	this->m_properties.Direction	= glm::vec3(-0.2f, -1.0f, -0.3f);
	this->m_properties.Ambient		= glm::vec3(0.2f);
	this->m_properties.Specular		= glm::vec3(0.2f);
	this->m_properties.Diffuse		= glm::vec3(0.2f);



	this->m_lightType				= DiffuseLighter;
}

void DiffuseLight::UpdateTargetShader(std::shared_ptr<Shader> shad, int index)
{
	shad->setVec3("dirlight.direction", m_properties.Direction);
	shad->setVec3("dirlight.ambient",	m_properties.Ambient);
	shad->setVec3("dirlight.diffuse",	m_properties.Specular);
	shad->setVec3("dirlight.specular",	m_properties.Diffuse);
}

DiffuseProperties& DiffuseLight::GetProperties()
{
	return this->m_properties;
}
