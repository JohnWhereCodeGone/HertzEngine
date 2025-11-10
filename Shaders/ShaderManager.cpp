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
    }

}


