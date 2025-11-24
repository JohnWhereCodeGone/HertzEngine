#include "PhysicsEngine2.h"
#include "../HertzEngine.h"
#include "../Entity/Entity.h"
#include "CubeCollider.h"

void PhysicsEngine2::Simulate(float DeltaTime)
{
	// this is meant to update visuals.
	std::vector<ColliderPtr> colliders = UpdatePhysicsScene();


	//checking for any collisions based on the shape ie Sphere-Sphere, Box-Box, Box-Sphere, 
	std::vector<Collision> collisions = CheckIntersections(colliders);


	//When Collided, what should happen?
	HandleCollisions(collisions);




	//Gravivty for now.
	ApplyVelocity(colliders, DeltaTime);



	//Update
}

void PhysicsEngine2::ApplyVelocity(std::vector<ColliderPtr> colliders, const float& deltaTime)
{

}

void PhysicsEngine2::HandleCollisions(std::vector<Collision> cols)
{

	//actual force logic here.

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

	for (ColliderPtr col1 : cols)
	{
		for (ColliderPtr col2 : cols)
		{
			if (col1 != col2)
			{
				
				if (CheckIntersect(col1, col2))
				{

					Collision coleMission;
					coleMission.col1 = col1;
					coleMission.col2 = col2;
					
					collisionsThisFrame.push_back(coleMission);

				}
				


			}


		}


	}

	return collisionsThisFrame;

}

bool PhysicsEngine2::CheckIntersect(ColliderPtr collider1, ColliderPtr collider2)
{
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



}

bool PhysicsEngine2::SphereSphereIntersect(const SphereCollider& sphere1, const SphereCollider& sphere2)
{
	float distance = glm::distance(sphere1.transformClass->GetPos(), sphere2.transformClass->GetPos());

	if (distance < sphere1.m_Radius + sphere2.m_Radius)
	{
		std::cout << "Spheres are Intersecting!!!!" << std::endl;
		return true;

	}
	else
	{
		return false;
	}

}

bool PhysicsEngine2::CubeCubeIntersect(const CubeCollider& cube1, const CubeCollider& cube2)
{

	
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


}
