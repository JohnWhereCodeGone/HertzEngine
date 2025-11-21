#pragma once
#include "Light.h"
#include "../glm/glm.hpp"

struct DiffuseProperties
{
    glm::vec3 Direction;
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;

};


class DiffuseLight : public Light
{
public:

	DiffuseLight();

    void UpdateTargetShader(std::shared_ptr<Shader> shad) override;
    
    DiffuseProperties& GetProperties();

private:

    DiffuseProperties m_properties;
};
