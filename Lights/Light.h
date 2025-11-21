#pragma once
#include "../glm/glm.hpp"
#include "../Shaders/HertzShader.h"



enum LightType
{
	Default,
	Diffuse,
	Specular,
	Spot
};

class Light
{
	
public:
	Light(const LightType& type = Default);

	virtual ~Light() = default;

	void			SetLightType(const LightType& type);
	LightType&		GetLightType();

	virtual void	UpdateTargetShader(std::shared_ptr<Shader> shad);


protected:

	LightType	m_lightType;

};

