#pragma once
#include "../Lights/DiffuseLight.h"
#include "../Lights/PointLight.h"
#include "../Lights/Spotlight.h"

class Lightmanager
{
	using LightPtr = std::shared_ptr<Light>;

public:

	std::shared_ptr<Light>			CreateLight(const LightType& type);
	void							DeleteLight(LightPtr toDelete);

	void							ApplyLights(std::shared_ptr<Shader> shad);
	const std::vector<LightPtr>&	GetLights();


private:

	std::vector<LightPtr> m_lightlist;

};

