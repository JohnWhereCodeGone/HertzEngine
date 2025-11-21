#include "ShaderManager.h"
#include "../Camera.h"
#include "../Lights/PointLight.h"

std::vector<std::shared_ptr<Shader>> ShaderManager::m_shaderList;

std::shared_ptr<Shader> ShaderManager::MakeShader(const char* tPath)
{

    ShaderPtr shad;

    

    if (tPath == nullptr)
    {
        shad = std::make_shared<Shader>();
    }
    else
    {
        shad = std::make_shared<Shader>(tPath);
    }

    if (!shad)
    {
        std::cout << "ShaderManager::MakeShader Error! Created shader resulted in nullptr." << std::endl;
        return nullptr;

    }




    m_shaderList.push_back(shad);
    return shad;

}

void ShaderManager::RemoveShader(ShaderPtr shadToRemove)
{

    if (!shadToRemove)
        return;

    //iterator
    auto toRemove = std::find(m_shaderList.begin(), m_shaderList.end(), shadToRemove);

    if (toRemove != m_shaderList.end())
    {
        m_shaderList.erase(toRemove);
    }

}


void ShaderManager::UpdateShaders(glm::mat4 projectionMat, glm::mat4 view, glm::vec3 camPos, std::shared_ptr<Camera> cam)
{

    for (auto it = m_shaderList.begin(); it != m_shaderList.end(); it++)
    {
        ShaderPtr shad = *it;
        if (!shad)
            continue;

        

        shad->Use();
        shad->setFloat("material.shine", 32.0f); //specifically, this one needs to be fixed/updated.
        shad->setMat4("projection", projectionMat);
        shad->setMat4("view", view);
        shad->setVec3("viewPos", camPos);
        shad->setVec3("lightPos", 1.2f, 1.0f, 2.0f);
        shad->setVec3("dirlight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        shad->setVec3("dirlight.ambient", glm::vec3(0.2f));
        shad->setVec3("dirlight.diffuse", glm::vec3(0.2f));
        shad->setVec3("dirlight.specular", glm::vec3(0.2f));
        shad->setVec3("pointLights[0].position", camPos);
        shad->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        shad->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        shad->setVec3("pointLights[0].specular", 0.0f, 1.0f, 0.0f);
        shad->setFloat("pointLights[0].constant", 1.f);
        shad->setFloat("pointLights[0].linear", 0.09f);
        shad->setFloat("pointLights[0].quadratic", 0.032f);
        shad->setBool("pointLights[0].shouldLight", true);
        shad->setVec3("spotLights[0].lightDir", cam->vFront);
        shad->setVec3("spotLights[0].pos", camPos);
        shad->setVec3("spotLights[0].spotDir", glm::vec3(0.0f, 0.0f, -1.f));
        shad->setVec3("spotLights[0].ambient", glm::vec3(0.2f));
        shad->setVec3("spotLights[0].diffuse", glm::vec3(0.2f));
        shad->setVec3("spotLights[0].specular", glm::vec3(0.2f));
        shad->setFloat("spotLights[0].constant", 1.f);
        shad->setFloat("spotLights[0].linear", 0.09f);
        shad->setFloat("spotLights[0].quadratic", 0.032f);
        shad->setFloat("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
        shad->setBool("spotLights[0].shouldLight", true);
        
        PointLight light;
        light.GetProperties().Specular = glm::vec3(1.0f, 0.0f, 1.0f);
        light.UpdateTargetShader(shad, 1);


    }

}


