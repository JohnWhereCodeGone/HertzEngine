#pragma once
#include "Light.h"
#include "../glm/glm.hpp"
#include "../Transform.h"
struct SpotLightProperties
{
	glm::vec3	LightDir;
	glm::vec3	SpotDir;
	glm::vec3	Ambient;
	glm::vec3	Diffuse;
	glm::vec3	Specular;

	float		Constant;
	float		Linear;
	float		Quadratic;
	float		Cutoff;
};



class Spotlight : public Light
{

public:
	Spotlight();
	void UpdateTargetShader(std::shared_ptr<Shader> shad, int index) override;



	std::shared_ptr<Transform> GetTrans();
	void					   SetTrans(std::shared_ptr<Transform> newtrans);
	bool& GetShouldLight();
	SpotLightProperties& GetProperties();

private:
	SpotLightProperties			m_properties;
	bool						m_bShouldLight;
	std::shared_ptr<Transform>	m_trans;
};

