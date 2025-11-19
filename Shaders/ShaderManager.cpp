#include "ShaderManager.h"


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

void ShaderManager::UpdateShaders(glm::mat4 projectionMat, glm::mat4 view, glm::vec3 camPos)
{

    for (auto it = m_shaderList.begin(); it != m_shaderList.end(); it++)
    {
        ShaderPtr shad = *it;
        if (!shad)
            continue;

        shad->Use();

        shad->setMat4("projection", projectionMat);
        shad->setMat4("view", view);
        shad->setVec3("viewPos", camPos);

        shad->setVec3("lightPos", 1.2f, 1.0f, 2.0f);

        

        shad->setVec3("dirlight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        shad->setVec3("dirlight.ambient", glm::vec3(0.2f));
        shad->setVec3("dirlight.diffuse", glm::vec3(0.2f));
        shad->setVec3("dirlight.specular", glm::vec3(0.2f));

        shad->setFloat("material.shine", 32.0f); //specifically, this one needs to be fixed/updated.


    }

}


