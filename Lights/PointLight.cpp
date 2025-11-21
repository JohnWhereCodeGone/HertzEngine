#include "PointLight.h"

PointLight::PointLight()
{
	this->m_properties.Position = glm::vec3(0.0f);
}

void PointLight::UpdateTargetShader(std::shared_ptr<Shader> shad)
{

}
