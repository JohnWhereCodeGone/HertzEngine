#include "Light.h"

Light::Light(const LightType& type)
{
	m_lightType = Default;
}

void Light::SetLightType(const LightType& type)
{
	this->m_lightType = type;
}

LightType& Light::GetLightType()
{
	return this->m_lightType;
}

void Light::UpdateTargetShader(std::shared_ptr<Shader> shad)
{

}
