#pragma once


//fix entity manager -> spawn entity, update pos etc ->

#include <vector>
#include "HertzShader.h"

class ShaderManager
{
public:

	using ShaderPtr = std::shared_ptr<Shader>;


	static ShaderPtr MakeShader(const char* tPath = nullptr);
	void RemoveShader(ShaderPtr shad);
	void UpdateShaders(glm::mat4 projectionMat, glm::mat4 view, glm::vec3 camPos);


private:

	
	static std::vector<ShaderPtr> m_shaderList;

};

