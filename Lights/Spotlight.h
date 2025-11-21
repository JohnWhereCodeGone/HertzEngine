#pragma once
#include "Light.h"

class Spotlight : public Light
{
	void UpdateTargetShader(std::shared_ptr<Shader> shad) override;
};

