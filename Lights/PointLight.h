#pragma once
#include "Light.h"
#include "../Transform.h"

struct PointLightProperties
{
	glm::vec3 Position; //transform
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	glm::vec3 constant;
	glm::vec3 linear;
	glm::vec3 Quadratic;
};

class PointLight : public Light
{
public:

	PointLight();
	Transform trans;

	void UpdateTargetShader(std::shared_ptr<Shader> shad) override;

private:
	PointLightProperties m_properties;

};

