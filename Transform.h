#pragma once

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"
#include "Shaders/HertzShader.h"


class vec3;



class Transform
{

public:
	
	Transform();
	Transform(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale, Shader* shader);

	//add vectors of motion for gravity etc
	glm::vec3& GetPos();
	glm::vec3& GetScale();
	glm::vec3& GetRot();

	void SetPos(const glm::vec3& newPos);
	void SetRot(const glm::vec3& newRot);
	void SetScale(const glm::vec3& newScale);
	void UpdateModel(Shader* shader);

	


private:
	
	glm::mat4 model;
	Shader* shader;
	glm::vec3 vPos;
	glm::vec3 vRotation;
	glm::vec3 vScale;
};

