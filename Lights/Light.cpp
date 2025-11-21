#include "Light.h"

void Light::SetLightType(const LightType& type)
{
	m_lightType = type;
}

LightType Light::GetLightType()
{
	return this->m_lightType;
}
