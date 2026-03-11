#pragma once

#include "../Dependencies/glm/glm.hpp"
#include "../Dependencies/glm/gtc/matrix_transform.hpp"
#include "Shaders/HertzShader.h"


class vec3;
class Camera;
class Entity;

constexpr double RENDER_SCALE = 1.0 / 10000000.0; //Rendering at one millionth the scale, 1 unit = 10000 km.





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
	glm::vec3&	GetRot();


	void SetPos(const glm::dvec3& newPos);
	void SetRot(const glm::vec3& newRot);
	void SetScale(const glm::vec3& newScale);
	
	void		UpdateModel(std::shared_ptr<Shader> shader);
	void		UpdateModelPlanetary(std::shared_ptr<Shader> shader, std::shared_ptr<Camera> cam);
	glm::dvec3&	GetVisualPos();
	double		GetRenderScale();

	const glm::mat4& GetModel();

	void AddPosKahan(const glm::dvec3& offset); //this doesn't work for some fucking reason.
	
	StellarType m_stellartype;
	glm::dquat	m_rotationQuat = glm::dquat(1, 0, 0, 0);

	//floating point origin
	std::shared_ptr<Entity> m_parent;


	glm::dvec3 m_localPos;
	glm::dvec3 m_prevLocalPos;
	glm::dvec3 m_interpolatedLocalPos;

	glm::dvec3 GetWorldPos() const;
	glm::dvec3 GetLocalPos() const;


private:
	
	glm::mat4				m_model;
	std::shared_ptr<Shader> m_shader;

	
	float m_VelocityDecayRate;

	
	glm::dvec3	m_vPosError;
	glm::dvec3	m_visualPos;
	glm::dvec3	m_vPos; //depricated, see m_localPos.
	glm::vec3	m_vRotation;
	glm::dvec3	m_vScale;
};

