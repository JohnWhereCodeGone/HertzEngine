#pragma once
#include "../Physics2/Collider.h"
#include "Collision.h"
#include <iostream>
#include "SphereCollider.h"
#include "CubeCollider.h"
#include "Raycast.h";

class HertzEngine;



struct AstronomyDebug
{
	double moonEarthDistance;
	double earthSunDistance;

	double OrbitalPeriodEarth;
	double OrbitalPeriodMoon;

	double TotalSystemMomentum;


};
constexpr double THREE_MONTHS = 3.0 * 27.321661 * 86400.0;


class PhysicsEngine2
{


private:


public:
	AstronomyDebug m_Debug;
	using ColliderPtr = std::shared_ptr<Collider>;


	void						timeSkip(double days);
	PhysicsEngine2				(HertzEngine& engineRef) : m_engineRef(engineRef), m_isSimulating(true), m_GravitationalConstant(6.67 * 10e-11f) {};
	void Simulate				(double DeltaTime);

	void ApplyVelocity			(std::vector<ColliderPtr> colliders, const float& deltaTime);
	void PlanetRotation(double dT);
	void HandleCollisions		(std::vector<Collision> cols);

	std::vector<ColliderPtr> UpdatePhysicsScene(); //depricated
	std::vector<Collision>	 CheckIntersections(std::vector<ColliderPtr> cols);

	Collision CheckIntersect			(ColliderPtr collider1, ColliderPtr collider2);
	bool CheckRayCastIntersect	(const Raycast& ray, ColliderPtr other);
	const RayHit& RayCast				(const glm::vec3& origin = glm::vec3(-1.f, 0.f, 0.f), const glm::vec3& direction = glm::vec3(0.0f, 0.0f, 1.0f));

	void EndStep(); //tf is this?

	Collision	SphereSphereIntersect	(const SphereCollider& sphere1, const SphereCollider& sphere2);
	Collision	CubeCubeIntersect		(const CubeCollider& cube1, const CubeCollider& cube2);
	Collision	CubeSphereIntersect		(const CubeCollider& cube, const SphereCollider& sphere);
	
	bool		RaySphereIntersect		(const Raycast& ray, std::shared_ptr<SphereCollider> sphere);
	bool		RayCubeIntersect		(const Raycast& ray, std::shared_ptr<CubeCollider> cube);
				
				
	void		UpdateVisuals			(const std::vector<ColliderPtr>& toUpdate, double trailDT);

	ColliderPtr CreateCollider	(const ColliderType& type, std::shared_ptr<Entity> parent);
	void		DeleteCollider	(ColliderPtr toDelete);

	void		ApplyGravity(float deltaTime);

	bool m_isSimulating;
	
	
	// Simulation methods & variables 
	void		ApplyNewtonianGravity();
	void		SatelliteMotion(double deltatime);
	double		m_GravitationalConstant;
	float		m_TimeScale = 150.0;
	bool		m_FastForward = false;
	double		m_FastForwardDuration;

	std::vector<ColliderPtr> m_colliderList;

private:


	HertzEngine& m_engineRef;

};

