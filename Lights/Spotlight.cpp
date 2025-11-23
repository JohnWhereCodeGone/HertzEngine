#include "Spotlight.h"

Spotlight::Spotlight()
{
    this->m_bShouldLight            = true;
    this->m_lightType               = LightType::Spotlighter;
    this->m_trans                   = std::make_shared<Transform>();

    this->m_properties.LightDir     = glm::vec3(0.0f, 0.0f, -1.0f);
    this->m_properties.SpotDir      = glm::vec3(0.0f, 0.0f, -1.f);
    this->m_properties.Ambient      = glm::vec3(0.2f);
    this->m_properties.Diffuse      = glm::vec3(0.2f);
    this->m_properties.Specular     = glm::vec3(0.2f);
    this->m_properties.Constant     = 1.0f;
    this->m_properties.Linear       = 0.09f;
    this->m_properties.Quadratic    = 0.032f;
    this->m_properties.Cutoff       = 12.5f;
}

void Spotlight::UpdateTargetShader(std::shared_ptr<Shader> shad, int index)
{
    shad->setVec3("spotLights[" + std::to_string(index) + "].pos",          m_trans->GetPos());
    shad->setFloat("spotLights[" + std::to_string(index) + "].cutOff",      glm::cos(glm::radians(m_properties.Cutoff)));

    shad->setVec3("spotLights[" + std::to_string(index) + "].lightDir",     m_properties.LightDir);
    shad->setVec3("spotLights[" + std::to_string(index) + "].ambient",      m_properties.Ambient);
    shad->setVec3("spotLights[" + std::to_string(index) + "].diffuse",      m_properties.Diffuse);
    shad->setVec3("spotLights[" + std::to_string(index) + "].specular",     m_properties.Specular);

    shad->setFloat("spotLights[" + std::to_string(index) + "].constant",    m_properties.Constant);
    shad->setFloat("spotLights[" + std::to_string(index) + "].linear",      m_properties.Linear);
    shad->setFloat("spotLights[" + std::to_string(index) + "].quadratic",   m_properties.Quadratic);
    shad->setBool( "spotLights[" + std::to_string(index) + "].shouldLight", m_bShouldLight);
}

std::shared_ptr<Transform> Spotlight::GetTrans()
{
    return this->m_trans;
}

void Spotlight::SetTrans(std::shared_ptr<Transform> newtrans)
{
    this->m_trans = newtrans;
}

bool& Spotlight::GetShouldLight()
{
    return this->m_bShouldLight;
}

SpotLightProperties& Spotlight::GetProperties()
{
    return this->m_properties;
}
