#pragma once
#include "../glm/glm.hpp"




enum LightType
{
	Default,
	Diffuse,
	Specular,
	Spot
};

class Light
{
	Light(const LightType& type);
	
	
	void		SetLightType(const LightType& type);
	
	
	LightType&	GetLightType();


private:


	LightType	m_lightType;

};

