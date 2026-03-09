#pragma once
#include "../glm/glm.hpp"
#include "iostream"
#include "../Transform.h"

enum ColliderType
{
	Sphere,
	Cube
};


class Entity;


struct RotationState
{
	glm::dvec3 axis;
	double angularSpeed;
	glm::dquat orientation; //fuck me.

};

class Collider
{
public:	
	
	virtual ~Collider() {}
	
	template<typename T>
	bool isOf() { return (dynamic_cast<T*>(this) != nullptr); };

	std::shared_ptr<Transform>		m_transform;
	glm::vec3						m_center;
									
	bool							m_bHasGravity;
	ColliderType					m_type;
	std::shared_ptr<Entity>			m_parent;
	bool							m_isKinematic;




	//Planetary Data Membersd
	glm::dvec3						m_force;
	double							m_mass;
	bool							m_isSatellite;
	
	glm::dvec3						m_velocity;
	glm::dvec3						m_acceleration;
	glm::dvec3						m_nextAcceleration;


	glm::dvec3						m_velocity_error;
	glm::dvec3						m_accelerationError;
	glm::dvec3						m_nAccelerationErrror;

	void AddAccelerationKhan();
	void AddVelocityKahan();
	void AddForceKhan();


	RotationState					m_rotationState;

};

