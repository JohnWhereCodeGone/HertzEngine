#pragma once


//fix entity manager -> spawn entity, update pos etc ->

#include <vector>
#include "HertzShader.h"

class Lightmanager;
class Camera;

class ShaderManager
{
public:

	using ShaderPtr = std::shared_ptr<Shader>;


	static ShaderPtr MakeShader(const char* tPath = nullptr);
	void RemoveShader(ShaderPtr shad);
	void UpdateShaders(glm::mat4 projectionMat, glm::mat4 view, glm::vec3 camPos, std::shared_ptr<Camera> cam, std::shared_ptr<Lightmanager> lightman = nullptr);



private:

	
	static std::vector<ShaderPtr> m_shaderList;

};

