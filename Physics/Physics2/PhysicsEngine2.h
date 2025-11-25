#pragma once
#include "../Physics2/Collider.h"
#include "Collision.h"
#include <iostream>
#include "SphereCollider.h"
#include "CubeCollider.h"
#include "Raycast.h";

class HertzEngine;



class PhysicsEngine2
{


private:


public:

	using ColliderPtr = std::shared_ptr<Collider>;

	PhysicsEngine2				(HertzEngine& engineRef) : m_engineRef(engineRef) {};
	void Simulate				(float DeltaTime);

	void ApplyVelocity			(std::vector<ColliderPtr> colliders, const float& deltaTime);
	void HandleCollisions		(std::vector<Collision> cols);

	std::vector<ColliderPtr> UpdatePhysicsScene(); //depricated
	std::vector<Collision>	 CheckIntersections(std::vector<ColliderPtr> cols);

	bool CheckIntersect			(ColliderPtr collider1, ColliderPtr collider2);
	bool CheckRayCastIntersect	(const Raycast& ray, ColliderPtr other);
	const RayHit& RayCast				(const glm::vec3& origin = glm::vec3(-1.f, 0.f, 0.f), const glm::vec3& direction = glm::vec3(0.0f, 0.0f, 1.0f));

	void EndStep(); //tf is this?

	bool SphereSphereIntersect	(const SphereCollider& sphere1, const SphereCollider& sphere2);
	bool CubeCubeIntersect		(const CubeCollider& cube1, const CubeCollider& cube2);
	bool CubeSphereIntersect	(const CubeCollider& cube, const SphereCollider& sphere);


	bool RaySphereIntersect		(const Raycast& ray, std::shared_ptr<SphereCollider> sphere);
	bool RayCubeIntersect		(const Raycast& ray, std::shared_ptr<CubeCollider> cube);


	void UpdateVisuals			(const std::vector<ColliderPtr>& toUpdate);

	ColliderPtr CreateCollider	(const ColliderType& type, std::shared_ptr<Entity> parent);
	void		DeleteCollider	(ColliderPtr toDelete);



private:

	std::vector<ColliderPtr> m_colliderList;

	HertzEngine& m_engineRef;

};

