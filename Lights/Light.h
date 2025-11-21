#pragma once
#include "../glm/glm.hpp"
#include "../Shaders/HertzShader.h"



enum LightType
{
	DefaultLight,
	DiffuseLighter,
	Spotlighter,
	Pointlighter
};

class Light
{
	
public:
	Light(const LightType& type = LightType::DefaultLight);

	virtual		~Light() = default;

	void			SetLightType(const LightType& type);
	LightType&		GetLightType();

	virtual void	UpdateTargetShader(std::shared_ptr<Shader> shad, int index);

	//for ui, defined in manager
	const char*			m_ID;

protected:

	LightType	m_lightType;

};

