#pragma once
#include "../Physics2/Collider.h"
#include "Collision.h"
#include <iostream>
#include "SphereCollider.h"
#include "CubeCollider.h"

class HertzEngine;



class PhysicsEngine2
{


private:


public:

	using ColliderPtr = std::shared_ptr<Collider>;

	PhysicsEngine2(HertzEngine& engineRef) : m_engineRef(engineRef) {};
	void Simulate(float DeltaTime);

	void ApplyVelocity(std::vector<ColliderPtr> colliders, const float& deltaTime);
	void HandleCollisions(std::vector<Collision> cols);

	std::vector<ColliderPtr> UpdatePhysicsScene();
	std::vector<Collision>	 CheckIntersections(std::vector<ColliderPtr> cols);

	bool CheckIntersect(ColliderPtr collider1, ColliderPtr collider2);

	void EndStep(); //tf is this?

	bool SphereSphereIntersect(const SphereCollider& sphere1, const SphereCollider& sphere2);
	bool CubeCubeIntersect(const CubeCollider& cube1, const CubeCollider& cube2);
	bool CubeSphereIntersect(const CubeCollider& cube, const SphereCollider& sphere);



private:

	std::vector<ColliderPtr> colliders;

	HertzEngine& m_engineRef;

};

