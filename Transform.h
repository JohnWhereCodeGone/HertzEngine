#pragma once

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"
#include "Shaders/HertzShader.h"


class vec3;



class Transform
{

public:
	
	Transform();
	Transform(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale, std::shared_ptr<Shader> shader);

	//add vectors of motion for gravity etc
	
	glm::vec3& GetPos();
	glm::vec3& GetScale();
	glm::vec3& GetRot();

	void SetPos(const glm::vec3& newPos);
	void SetRot(const glm::vec3& newRot);
	void SetScale(const glm::vec3& newScale);
	void AddVelocity(const glm::vec3& addedVelocity);
	void AddVelocity(float x = 0, float y = 0, float z = 0);
	
	void UpdateModel(std::shared_ptr<Shader> shader);
	void Move(float DeltaTime);

	const glm::mat4& GetModel();
	


private:
	
	glm::mat4 m_model;
	std::shared_ptr<Shader> m_shader;

	
	float m_VelocityDecayRate;

	


	glm::vec3 m_vVelocity;
	glm::vec3 m_vPos;
	glm::vec3 m_vRotation;
	glm::vec3 m_vScale;
};

