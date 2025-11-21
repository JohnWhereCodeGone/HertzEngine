#include "PointLight.h"

PointLight::PointLight()
{

    this->m_properties.Ambient   =      glm::vec3(0.05f, 0.05f, 0.05f);
    this->m_properties.Diffuse   =      glm::vec3(0.8f);
    this->m_properties.Specular  =      glm::vec3(0.8f);
   
    this->m_properties.Constant  =      1.f;
    this->m_properties.Linear    =      0.09f;
    this->m_properties.Quadratic =      0.032f;
    this->m_lightType            =      LightType::Pointlighter;


    m_trans = std::make_shared<Transform>();
    m_bShouldLight = true;
}

std::shared_ptr<Transform> PointLight::GetTransform()
{
    return this->m_trans;
}

void PointLight::UpdateTargetShader(std::shared_ptr<Shader> shad, int index)
{
    shad->setVec3("pointLights[" + std::to_string(index) + "].position",     m_trans->GetPos());
    shad->setVec3("pointLights[" + std::to_string(index) + "].ambient",      m_properties.Ambient);
    shad->setVec3("pointLights[" + std::to_string(index) + "].diffuse",      m_properties.Diffuse);
    shad->setVec3("pointLights[" + std::to_string(index) + "].specular",     m_properties.Specular);

    shad->setFloat("pointLights[" + std::to_string(index) + "].constant",    m_properties.Constant);
    shad->setFloat("pointLights[" + std::to_string(index) + "].linear",      m_properties.Linear);
    shad->setFloat("pointLights[" + std::to_string(index) + "].quadratic",   m_properties.Quadratic);
    shad->setBool("pointLights[" + std::to_string(index) + "].shouldLight",  m_bShouldLight);
}

bool& PointLight::GetShouldLight()
{
    return this->m_bShouldLight;
}

PointLightProperties& PointLight::GetProperties()
{
    return this->m_properties;
}
