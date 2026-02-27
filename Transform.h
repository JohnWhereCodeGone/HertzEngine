#pragma once

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"
#include "Shaders/HertzShader.h"


class vec3;
class Camera;

constexpr double RENDER_SCALE = 1.0 / 1000000.0; //Rendering at one millionth the scale, 1 unit = 1000 km.


enum StellarType
{
	UNSPECIFIED,
	STAR,
	PLANET,
};


class Transform
{

public:
	
	Transform();
	Transform(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale, std::shared_ptr<Shader> shader);

	//add vectors of motion for gravity etc
	
	glm::dvec3& GetPos();
	glm::dvec3& GetScale();
	glm::vec3& GetRot();
	glm::vec3& GetVelocity();


	void SetPos(const glm::dvec3& newPos);
	void SetRot(const glm::vec3& newRot);
	void SetScale(const glm::vec3& newScale);
	void AddVelocity(const glm::vec3& addedVelocity);
	void AddVelocity(float x = 0, float y = 0, float z = 0); //I don't work, lol.
	
	void UpdateModel(std::shared_ptr<Shader> shader);
	void UpdateModelPlanetary(std::shared_ptr<Shader> shader, std::shared_ptr<Camera> cam);
	glm::vec3& GetVisualPos();
	double GetRenderScale();
	void Move(float DeltaTime);

	const glm::mat4& GetModel();
	
	StellarType m_stellartype;
	glm::dquat m_rotationQuat = glm::dquat(1, 0, 0, 0);


private:
	
	glm::mat4 m_model;
	std::shared_ptr<Shader> m_shader;

	
	float m_VelocityDecayRate;

	

	glm::vec3 m_visualPos;
	glm::vec3 m_vVelocity;
	glm::dvec3 m_vPos;
	glm::vec3 m_vRotation;
	glm::dvec3 m_vScale;
};

