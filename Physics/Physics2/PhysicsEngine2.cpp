#include "PhysicsEngine2.h"
#include "../HertzEngine.h"
#include "../Entity/Entity.h"
#include "CubeCollider.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "../glm/gtx/norm.hpp"
#include "../glm/ext/matrix_common.hpp"
#include "../Entity/EntityManager.h"

constexpr double OFFSET = 1e-7;
constexpr double TRAIL_DELAY = 60;

void PhysicsEngine2::timeSkip(double days)
{
	m_FastForward = true;
	m_FastForwardDuration = 86400.0 * days; //seconds in day * amount of days

}

void PhysicsEngine2::Simulate(double DeltaTime)
{
	// this is meant to update visuals.
	if (m_colliderList.empty())
	{
		return;
	}

	// UPDATE POS, CLEAR FORCES & RECOMPUTE ACCELERATION, UPDATE VELOCITY (V += 0.5 * (acceleration * newacceleration * dt), STORE NEW ACCELERATION) 
	//clear forces after each step or F will accumulate and break everything.


	//std::vector<Collision> collisions = CheckIntersections(m_colliderList);

	for (ColliderPtr col : m_colliderList)
	{
		if (!col->m_isSatellite)
			continue;
		glm::dvec3 pos = col->m_transform->GetPos();

		glm::dvec3 nPos = col->m_velocity * DeltaTime + 0.5 * col->m_acceleration * DeltaTime * DeltaTime;
		
		glm::dvec3 resault = nPos + pos;

		col->m_transform->SetPos(resault);

		col->m_force = glm::dvec3(0);
	}


	//checking for any collisions based on the shape ie Sphere-Sphere, Box-Box, Box-Sphere, 



	//ApplyGravity(DeltaTime);
	ApplyNewtonianGravity();


	for (ColliderPtr col : m_colliderList)
	{

		if (!col->m_isSatellite)
			continue;
		
		col->m_nextAcceleration = col->m_force/col->m_mass;

		//new velocity--

		col->m_velocity += 0.5 * (col->m_acceleration + col->m_nextAcceleration) * DeltaTime;

		col->m_acceleration = col->m_nextAcceleration;
	}

	//When Collided, what should happen?
	//HandleCollisions(collisions);




	//Gravivty for now.
	//SatelliteMotion(DeltaTime);
	//ApplyVelocity(m_colliderList, DeltaTime);

	PlanetRotation(DeltaTime);

	//Update Visuals //BUG: SPHERE DOESN'T WORK
	UpdateVisuals(m_colliderList, DeltaTime);





}


void PhysicsEngine2::UpdateVisuals(const std::vector<ColliderPtr>& toUpdate, double trailDT)
{
	/*
	for (auto& col : toUpdate)
	{

		if (col->m_isSatellite && col->m_parent)
		{
			SphereCollider* planet = std::static_pointer_cast<SphereCollider>(col).get();
			Trail* trailer = planet->m_trail.get();

			trailer->m_Accumulator += trailDT;

			if (trailer->m_Accumulator >= TRAIL_DELAY)
			{
				
				if (trailer->points.size() >= trailer->m_maxPoints)
				{
					trailer->points.pop_front();
				}
				trailer->points.push_back(planet->m_transform->GetVisualPos());

				trailer->m_Accumulator = 0.0;
				

			}

			

			


		}

		



	*/







	/*


	for (ColliderPtr col : toUpdate)
	{
		if (col->m_parent)
		{
			if (col->isOf<CubeCollider>())
			{
				std::shared_ptr<CubeCollider> cube	= std::static_pointer_cast<CubeCollider>(col);

				cube->m_Dimensions = cube->m_BaseDimensions * cube->m_transform->GetScale();

			}

			if (col->isOf<SphereCollider>())
			{
				std::shared_ptr<SphereCollider> sphere = std::static_pointer_cast<SphereCollider>(col);

				glm::dvec3& scale = sphere->m_transform->GetScale();

				float largestAxis = glm::max(scale.x, glm::max(scale.y, scale.z));
				
				sphere->m_Radius = largestAxis * sphere->m_BaseRadius;

			}



		}


	}

	*/

}
void PhysicsEngine2::ApplyVelocity(std::vector<ColliderPtr> colliders, const float& deltaTime)
{
	for (ColliderPtr col : m_colliderList)
	{
		if (col->m_bHasGravity)
		{

			glm::vec3 pos = col->m_transform->GetPos();
			pos += col->m_transform->GetVelocity() * deltaTime;
			col->m_transform->SetPos(pos);
			

		}

	}
}

void PhysicsEngine2::PlanetRotation(double dT)
{
	for (auto& col : m_colliderList)
	{
		if (col->m_isSatellite)
		{
			RotationState& state = col->m_rotationState;

			double angle = state.angularSpeed * dT;
			glm::dquat q = glm::angleAxis(angle, state.axis);

			state.orientation = glm::normalize(q * state.orientation);

			if (col->m_transform)
			{
				col->m_transform->m_rotationQuat = state.orientation;
			}


		}


	}
}

void PhysicsEngine2::HandleCollisions(std::vector<Collision> cols)
{
	/*

	for (Collision& col : cols)
	{
		auto& a = col.m_col1;
		auto& b = col.m_col2;


		glm::vec3 normal = glm::normalize(b->m_transform->GetPos() - b->m_transform->GetPos());
		
		if (glm::length2(normal) < 0.000001f)
		{
			normal = glm::vec3(0.1f);
		}

		glm::vec3 deltaV = b->m_transform->GetVelocity() - a->m_transform->GetVelocity();

		float velocityAlongNormal = glm::dot(deltaV, normal);

		if (velocityAlongNormal < 0)
		{
			float restitution = 0.1f;
			float impulse = (1 + restitution) * velocityAlongNormal;

			glm::vec3 impulseVector = impulse * normal;

			if (!a->m_isKinematic)
			{
				a->m_transform->GetVelocity() += impulseVector;
				glm::vec3 r = col.m_point + a->m_transform->GetPos();
				a->

			}
			if (!b->m_isKinematic)
			{

			}
		}


	}
	*/

	for (Collision& col : cols)
	{
		auto& a = col.m_col1;
		auto& b = col.m_col2;

		float push = 20.f;
		glm::vec3 normal = glm::normalize(b->m_transform->GetPos() - a->m_transform->GetPos());
		if (glm::length2(normal) < 0.000001f)
		{
			normal = glm::vec3(1.f, 0.0f, 0.f);
		}

		if (!a->m_isKinematic)
		{
			a->m_transform->GetVelocity() *= -1;
			//a->m_transform->SetPos(a->m_transform->GetPos() + normal * push);

		}
		if (!b->m_isKinematic)
		{
			b->m_transform->GetVelocity() *= -1;
			//b->m_transform->SetPos(a->m_transform->GetPos() - normal * push);
		}
	}

}

std::vector<std::shared_ptr<Collider>> PhysicsEngine2::UpdatePhysicsScene()
{
	//this is terrible, reconstructing it every frame lmao

	std::vector<std::shared_ptr<Collider>> collidersInScene;

	for (auto& en : m_engineRef.GetEntityManager()->m_entityList)
	{
		if (en->GetCollider() != nullptr)
		{
			collidersInScene.push_back(en->GetCollider());

		}
		

	}
	return collidersInScene;
}

std::vector<Collision> PhysicsEngine2::CheckIntersections(std::vector<ColliderPtr> cols)
{ 
	

	std::vector<Collision> collisionsThisFrame;

	int size = cols.size();

	for (int i = 0; i < size; i++)
	{


		for (int j = i + 1; j < size; j++)
		{

			Collision c = CheckIntersect(cols[i], cols[j]);

			if (c.m_col1 != nullptr && c.m_col2 != nullptr && c.m_hasCollided)
			{

				
				collisionsThisFrame.push_back(c);


			}

		}
	}
	
	/* old shit
	for (ColliderPtr col1 : cols)
	{
		for (ColliderPtr col2 : cols)
		{
			if (col1 != col2)
			{
				
				if (CheckIntersect(col1, col2))
				{

					Collision coleMission;
					coleMission.m_col1 = col1;
					coleMission.m_col2 = col2;
					
					if (col1 && col2)
					{
						collisionsThisFrame.push_back(coleMission);
					}

				}
				


			}


		}


	}
	*/

	return collisionsThisFrame;

}

Collision PhysicsEngine2::CheckIntersect(ColliderPtr collider1, ColliderPtr collider2)
{
	Collision cole;
	if (collider1->isOf<SphereCollider>() && collider2->isOf<SphereCollider>())
	{
		std::shared_ptr<SphereCollider> sphere1 = std::static_pointer_cast<SphereCollider>(collider1);
		std::shared_ptr<SphereCollider> sphere2 = std::static_pointer_cast<SphereCollider>(collider2);

		return SphereSphereIntersect(*sphere1, *sphere2);

	}

	if (collider1->isOf<CubeCollider>() && collider2->isOf<CubeCollider>())
	{

		std::shared_ptr<CubeCollider> cube1 = std::static_pointer_cast<CubeCollider>(collider1);
		std::shared_ptr<CubeCollider> cube2 = std::static_pointer_cast<CubeCollider>(collider2);

		
		return CubeCubeIntersect(*cube1, *cube2);

	}

	if (collider1->m_type == Sphere && collider2->m_type == Cube)
	{
		std::shared_ptr<CubeCollider> cube = std::static_pointer_cast<CubeCollider>(collider2);
		std::shared_ptr<SphereCollider> sphere = std::static_pointer_cast<SphereCollider>(collider1);


		return CubeSphereIntersect(*cube, *sphere);
	}
	/*
	else if (collider2->isOf<SphereCollider>() && collider2->isOf<CubeCollider>())
	{
		std::shared_ptr<CubeCollider> cube = std::static_pointer_cast<CubeCollider>(collider2);
		std::shared_ptr<SphereCollider> sphere = std::static_pointer_cast<SphereCollider>(collider1);


		return CubeSphereIntersect(*cube, *sphere);
	}
	*/



}

bool PhysicsEngine2::CheckRayCastIntersect(const Raycast& ray, ColliderPtr other)
{
	bool hasHit = false;
	switch (other->m_type)
	{
		case(Cube):
		{

			std::shared_ptr<CubeCollider> cube = std::static_pointer_cast<CubeCollider>(other);
			hasHit = RayCubeIntersect(ray, cube);
			break;
		}

		case(Sphere):
			
		{
			std::shared_ptr<SphereCollider> sphere = std::static_pointer_cast<SphereCollider>(other);
			hasHit = RaySphereIntersect(ray, sphere);
			break;

		}


	}
	return hasHit;

}

const RayHit& PhysicsEngine2::RayCast(const glm::vec3& origin, const glm::vec3& direction)
{
	Raycast ray = Raycast(origin, direction);
	RayHit hit;


	for (ColliderPtr col : m_colliderList)
	{
		if (CheckRayCastIntersect(ray, col))
		{
			glm::vec3 cubepos = glm::vec3(0.f);





			if (col->m_type == Cube)
			{
				std::shared_ptr<CubeCollider> cube = std::static_pointer_cast<CubeCollider>(col);
				hit.m_distance = glm::length((glm::dvec3)origin - col->m_transform->GetPos() + cube->m_Dimensions * 0.5);

			}
			else if (col->m_type == Sphere)
			{
				std::shared_ptr<SphereCollider> sphere = std::static_pointer_cast<SphereCollider>(col);
				hit.m_distance = glm::length((glm::dvec3)origin - col->m_transform->GetPos() - sphere->m_Radius);
			}

			hit.m_collider = col;
			hit.m_point = cubepos;
			//std::cout << "ray distance: " << hit.m_distance << std::endl;

			return hit;

		}


	}

	return hit;

}


Collision PhysicsEngine2::SphereSphereIntersect(const SphereCollider& sphere1, const SphereCollider& sphere2)
{
	float distance = glm::distance(sphere1.m_transform->GetPos(), sphere2.m_transform->GetPos());

	glm::dvec3 collisionNormal = (glm::normalize(sphere2.m_transform->GetPos() - sphere1.m_transform->GetPos()));



	if (distance < sphere1.m_Radius + sphere2.m_Radius)
	{
		//std::cout << "Spheres are Intersecting!!!!" << std::endl;
		Collision col;
		
		col.m_col1 = sphere1.m_parent->GetCollider().get();
		col.m_col2 = sphere2.m_parent->GetCollider().get();

		col.m_point = sphere1.m_transform->GetPos() + collisionNormal * sphere1.m_Radius;
		col.m_hasCollided = true;
		return col;

	}
	else
	{
		return Collision();
	}

}

Collision PhysicsEngine2::CubeCubeIntersect(const CubeCollider& cube1, const CubeCollider& cube2)
{

	/*
	glm::vec3 max1 = cube1.transformClass->GetPos() + (glm::vec3(cube1.m_Dimensions.x / 2, cube1.m_Dimensions.y / 2, cube1.m_Dimensions.z / 2));
	glm::vec3 min1 = cube1.transformClass->GetPos() - (glm::vec3(cube1.m_Dimensions.x / 2, cube1.m_Dimensions.y / 2, cube1.m_Dimensions.z / 2));


	glm::vec3 max2 = cube2.transformClass->GetPos() + (glm::vec3(cube2.m_Dimensions.x / 2, cube2.m_Dimensions.y / 2, cube2.m_Dimensions.z / 2));
	glm::vec3 min2 = cube2.transformClass->GetPos() - (glm::vec3(cube2.m_Dimensions.x / 2, cube2.m_Dimensions.y / 2, cube2.m_Dimensions.z / 2));

	if (max1.x >= min2.x && min1.x <= max2.x && max1.y >= min2.y && min1.y <= max2.y && max1.z >= min2.z && min1.z <= max2.z)
	{
		std::cout << "Cubes are intersecting!!!!!" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
	*/

	glm::mat3 rotation1 = glm::mat3(cube1.m_transform->GetModel());
	glm::mat3 rotation2 = glm::mat3(cube2.m_transform->GetModel());
	glm::vec3 translation = glm::vec3(cube2.m_transform->GetPos()) - glm::vec3(cube1.m_transform->GetPos());

	translation = glm::transpose(rotation1) * translation;

	glm::mat3 rotation = glm::transpose(rotation1) * rotation2;
	glm::mat3 absRotation = glm::abs(rotation) + glm::mat3(0.0001f);


	glm::vec3 halfSize1 = cube1.m_Dimensions * 0.5;
	glm::vec3 halfSize2 = cube2.m_Dimensions * 0.5;
	


	for (int i = 0; i < 3; i++)
	{
		float ra = halfSize1[i];
		float rb = glm::dot(absRotation[i], halfSize2);
		if (glm::abs(translation[i]) > ra + rb)
		{
			return Collision();
		}
	}
	for (int i = 0; i < 3; i++)
	{
		float ra = glm::dot(absRotation[i], halfSize1);
		float rb = halfSize2[i];
		if (glm::abs(glm::dot(rotation[i], translation)) > ra + rb)
		{
			return Collision();
		}
	}

	Collision col;
	col.m_col1 = cube1.m_parent->GetCollider().get();
	col.m_col2 = cube2.m_parent->GetCollider().get();

	glm::vec3 collisionNormal = glm::vec3(cube1.m_transform->GetPos() - cube2.m_transform->GetPos());
	col.m_point = (col.m_col1->m_transform->GetPos() + col.m_col2->m_transform->GetPos()) * 0.5;

	std::cout << "Cube-cube collision!!" << std::endl;
	col.m_hasCollided = true;
	return col;
}

Collision PhysicsEngine2::CubeSphereIntersect(const CubeCollider& cube, const SphereCollider& sphere)
{
	if(!cube.m_parent || !sphere.m_parent)
	{
		return Collision();
	}
	glm::vec3 sphereCenter = sphere.m_transform->GetPos();
	glm::vec3 localSphereCenter = glm::inverse(cube.m_transform->GetModel()) * glm::vec4(sphereCenter, 1.0f); //moves sphere into local space of cube

	glm::vec3 closestPoint = glm::clamp(localSphereCenter, - (glm::vec3)cube.m_Dimensions * glm::vec3(0.5), (glm::vec3)cube.m_Dimensions * glm::vec3(0.5));

	float distance = glm::length2(localSphereCenter - closestPoint);



	if (distance < (sphere.m_Radius * sphere.m_Radius))
	{
		std::cout << "Sphere-Cube Collision Occuring" << std::endl;
		Collision col;
		col.m_col1 = cube.m_parent->GetCollider().get();
		col.m_col2 = sphere.m_parent->GetCollider().get();

		glm::vec3 normalLocal = localSphereCenter - closestPoint;
		glm::vec3 normalWorld = glm::normalize(glm::mat3(cube.m_transform->GetModel()) * normalLocal);
		col.m_normal = normalWorld;

		col.m_point = glm::vec3(cube.m_transform->GetModel() * glm::vec4(closestPoint, 1.0f));

		col.m_hasCollided = true;
		return col;
	}
	else
	{
		return Collision();
	}

}

bool PhysicsEngine2::RaySphereIntersect(const Raycast& ray, std::shared_ptr<SphereCollider> sphere)
{
	glm::dvec3 originToSphere = sphere->m_transform->GetPos() - ray.m_origin;
	float t0 = glm::dot(originToSphere, ray.m_direction);
	float distSq = glm::dot(originToSphere, originToSphere) - t0 * t0;
	float radSq = sphere->m_Radius * sphere->m_Radius;

	if (distSq > radSq)
	{
		return false;
	}

	float t1 = glm::sqrt(radSq - distSq);
	float eps = 1.e-6f;
	float intersectDist = (t1 > t1 + eps) ? t0 - t1 : t0 + 1;

	if (intersectDist > eps)
	{

		//std::cout << "You hit a sphere, congrats" << std::endl;
		return true;

	}
	else
	{
		return false;
	}



}

bool PhysicsEngine2::RayCubeIntersect(const Raycast& ray, std::shared_ptr<CubeCollider> cube)
{
	glm::mat4 inverse = glm::inverse(cube->m_transform->GetModel());
	glm::vec3 localRayCenter = glm::vec3(inverse * glm::vec4(ray.m_origin, 1));
	glm::vec3 localRayDir = glm::normalize(glm::vec3(inverse * glm::vec4(ray.m_direction, 0)));

	glm::dvec3 min = -cube->m_Dimensions * 0.5;
	glm::dvec3 max = cube->m_Dimensions * 0.5;

	float eds = 1.e-6f;


	glm::vec3 invDir = glm::vec3(1.0f) / localRayDir;



	float t1 = (min.x - localRayCenter.x) * invDir.x;
	float t2 = (max.x - localRayCenter.x) * invDir.x;
	float t3 = (min.y - localRayCenter.y) * invDir.y;
	float t4 = (max.y - localRayCenter.y) * invDir.y;
	float t5 = (min.z - localRayCenter.z) * invDir.z;
	float t6 = (max.z - localRayCenter.z) * invDir.z;

	float tMin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tMax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	if (tMax < 0)
	{
		return false;
	}

	if (tMin > tMax)
	{
		//something has been hit from the front
		return false;
	}

	//std::cout << "Raycast hit entity w/ cube collider: " << cube->m_parent->GetName() << std::endl;
	return true;

}



std::shared_ptr<Collider> PhysicsEngine2::CreateCollider(const ColliderType& type, std::shared_ptr<Entity> parent)
{
	std::shared_ptr<Collider> toReturn;
	switch (type)
	{
	case(Cube):
		toReturn = std::make_shared<CubeCollider>(parent);
		break;

	case(Sphere):
		toReturn = std::make_shared<SphereCollider>(parent);
		break;
	}

	if (toReturn)
	{
		this->m_colliderList.push_back(toReturn);
		return toReturn;
	}
	else
	{
		return nullptr;
	}

}

void PhysicsEngine2::DeleteCollider(ColliderPtr toDelete)
{
	auto it = std::find(m_colliderList.begin(), m_colliderList.end(), toDelete);
	m_colliderList.erase(it);
}

void PhysicsEngine2::ApplyNewtonianGravity()
{
	for (int i = 0; i < m_colliderList.size(); i++)
	{


		for (int j = i + 1; j < m_colliderList.size(); j++)
		{
			// F = G * (m1 * m2 / r^2)
			ColliderPtr col1 = m_colliderList[i];
			ColliderPtr col2 = m_colliderList[j];
			if (!col1->m_isSatellite || !col2->m_isSatellite)
			{
				continue;
			}


			glm::dvec3 distance = col2->m_transform->GetPos() - col1->m_transform->GetPos();

			//r^2
			double distSqr = glm::length2(distance) + OFFSET;

			// m1 * m2
			double massProduct = col1->m_mass * col2->m_mass;
			

			double ddist = glm::length(distance);
			if (ddist < OFFSET)
			{
				continue; // prevent NaN if they get too close - skip gravity.
			}
			glm::dvec3 distanceNorm = distance / ddist;

			double GravForce = m_GravitationalConstant * (massProduct / distSqr);


			glm::dvec3 result = distanceNorm * GravForce;

			if (col1->m_isSatellite)
			{
				col1->m_force += result;

			}
			if (col2->m_isSatellite)
			{
				col2->m_force -= result;
			}


			


			

		}


	}

}

void PhysicsEngine2::SatelliteMotion(double deltaTime)
{

	for (auto& col : m_colliderList)
	{

		//semi-implicit euler for now, update me to
		constexpr double offset = 1e-6;
		
		glm::dvec3 acceleration = (col->m_force / col->m_mass);
		col->m_velocity += acceleration * deltaTime;
		col->m_force = glm::dvec3(0);


		glm::dvec3 pos = col->m_transform->GetPos();

		pos += col->m_velocity * deltaTime;
		col->m_transform->SetPos(pos);

	}

}

void PhysicsEngine2::ApplyGravity(float deltaTime)
{
	//this doesn't need deltatime.

	for (ColliderPtr col : m_colliderList)
	{
		if (col->m_bHasGravity && !col->m_isKinematic)
		{
			glm::vec3& velocity = col->m_transform->GetVelocity();
			float Gravity = 0.2f;

			velocity += glm::vec3(0.0f, -Gravity, 0.0f);
		}

	}

}
