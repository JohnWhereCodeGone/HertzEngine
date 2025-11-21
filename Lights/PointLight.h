#pragma once
#include "Light.h"
#include "../Transform.h"

struct PointLightProperties
{
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Constant;
	float Linear;
	float Quadratic;
};

class PointLight : public Light
{
public:

	PointLight();
	
	std::shared_ptr<Transform> GetTransform();
	void UpdateTargetShader(std::shared_ptr<Shader> shad, int index) override;
	bool& GetShouldLight();
	PointLightProperties& GetProperties();

private:


	std::shared_ptr<Transform>  m_trans;
	bool						m_bShouldLight;
	PointLightProperties		m_properties;

};

