#pragma once
#include <iostream>
#include "../Physics/Physics2\AstronomicalData.h"
#include "../UI/HertzEditor.h"
//ui


#include "glad/glad.h" // manages function pointers for OpenGL
#include "glfw3.h"
#include "../Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

#include "Camera.h"
#include <thread>

#include "Shaders/HertzShader.h"
#include <filesystem>
#include "Texture/HertzTexture.h"

#include "Camera.h"

//objects
#include "Mesh.h"
#include "ObjLoader.h"
#include "../Mesh/Meshmanager.h"
#include "HertzEngine.h"
#include "Objects/VirtualObject.h"
#include "Entity/Entity.h"
#include "Serializer/Serializer.h"

#include "../Lights/Lightmanager.h"
#include "../Physics/Physics2/CubeCollider.h"
#include "Physics/Physics2/PhysicsEngine2.h"
#include "../Transform.h"
std::string crate = ".\\Dependencies\\Crate.obj";
std::string monky = ".\\Dependencies\\monkey.obj";
std::string sphere = ".\\Mesh\\sphere2.obj";
#include "../Entity/EntityManager.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "../glm/gtx/string_cast.hpp"

//TODO:
// FIXED - TUTORIAL, FIXED SUN SHADER
// Create and fix Orbital Trail
// Create and fix Astronomy Data & Window per camera planet view
// Create and fix ...


double ijrtdh = glm::two_pi<double>();




//ALL CONSTANTS IN SI UNITS

constexpr double c_EarthRadius = 6.3781e6; 
constexpr double c_MoonRadius = 1737400;
constexpr double c_sunRadius = 6.9634e8;

constexpr double c_EarthMass = 5.9722e24;
constexpr double c_MoonMass = 7.35e22;
constexpr double c_SunMass = 1.989e30;


constexpr double G = 6.67430e-11;


constexpr double AU = 1.495978707e11;
constexpr double c_MoonsOffset = 3.844e8;


constexpr double earthRotationSeconds = 86164.0905;
constexpr double earthOmega = glm::two_pi<double>() / earthRotationSeconds;


constexpr glm::dvec3 c_EarthStartPos = glm::dvec3(AU, 0, 0);
constexpr glm::dvec3 c_MoonStartPos = c_EarthStartPos + glm::dvec3(c_MoonsOffset, 0, 0);

// EARTH ORBIT, 23.5 deg, perpendicular perfectly circular.
double rad = glm::radians(23.5);

glm::dvec3 orbitNormal = glm::normalize(glm::dvec3(0.0, 1.0, 0.0));
glm::dvec3 vDir = glm::normalize(glm::cross(orbitNormal, glm::normalize(c_EarthStartPos))); // earth orbits 23.5 deg of barycenter.

//ROTATIONS

RotationState stateEarth;
RotationState stateMoon;


//MOON ORBIT

glm::dvec3 distMoon = c_MoonStartPos - c_EarthStartPos;
double		moonIncline = glm::radians(5.145);
glm::dvec3 tempp = glm::normalize(glm::cross(orbitNormal, distMoon));
glm::dquat q = glm::angleAxis(moonIncline, tempp);

glm::dvec3 lunarNormal = glm::normalize(q * orbitNormal);
glm::dvec3 lunarDir = glm::normalize(glm::cross(lunarNormal, glm::normalize(distMoon)));


//BUG: Changing mesh overwrites entity shader.


// have the main thread check its own list for pushed data from other threads.
//STOLEN
double OrbitalPeriod(double distance, double massPrimary, double massSecondary)
{
	double mu = G * (massPrimary + massSecondary);
	return glm::two_pi<double>() * std::sqrt((distance * distance * distance) / mu);
}
//STOLEN
double RotationalPeriod(double angularSpeed)
{
	return glm::two_pi<double>() / angularSpeed;
}

static double CircularOrbitVelocity(std::shared_ptr<Entity> targetofOrbit, double distance, double mass)
{
	
	double GMproduct = mass * G;

	double result = glm::sqrt(GMproduct / distance);


	std::cout << "ORBITAL VELOCITY: " << result << " m/s" << std::endl;

	return result;

}


int main()
{ 

	/*  Rotation States for Moon and the Earth  */

	stateEarth.orientation = glm::angleAxis(glm::radians(23.5), glm::dvec3(1, 0, 0));
	stateEarth.angularSpeed = earthOmega;
	stateEarth.axis = orbitNormal;





	//////////////////////////////////////////////


	double moonVelocity;
	double sunVelocity;
	double earthVelocity;


	using EntityPtr = std::shared_ptr<Entity>;
	HertzEngine engine;

	GLFWwindow* win = engine.GetWindow();
	std::shared_ptr<PhysicsEngine2> physics = engine.GetPhysicsEngine();

	std::shared_ptr<Lightmanager> lightman = engine.GetLightManager();
	
	
	std::shared_ptr<PointLight> sunlight = std::static_pointer_cast<PointLight>(lightman->CreateLight(Pointlighter));

	PointLightProperties& prop = sunlight->GetProperties();

	prop.Quadratic = 0.0;
	prop.Linear = 0.0;
	prop.Diffuse = glm::vec3(3, 3, 3);
	prop.Ambient = glm::vec3(0.1f);
	sunlight->GetTransform()->SetPos(glm::dvec3(0.0));

	//lightman->CreateLight(DiffuseLighter);
	
	auto EntityManager = engine.GetEntityManager();

	engine.GetMeshMangr()->LoadDataMesh();



	/* S U N */
	std::shared_ptr<Entity> Sun = EntityManager->CreateEntity();
	Sun->m_isSatellite = true;
	Sun->GetTransform()->m_localPos = (glm::dvec3(0.0, 0.0, 0.0));
	Sun->GetTransform()->m_stellartype = STAR;
	Sun->SetName("Sol");
	Sun->SetMesh(engine.GetMeshMangr()->GetMeshByName("sphere2"));

	Sun->SetDiffuseMap(engine.GetTextureManager()->LoadTexture(".\\Texture\\8k_sun.jpg", Diffuse));
	Sun->SetSpecularMap(engine.GetTextureManager()->LoadTexture(".\\Texture\\8k_sun.jpg", Specular));


	Sun->SetShader(engine.GetShaderManager()->MakeShader(".\\Shaders\\unlitFragment.glsl"));

	//radius

	glm::dvec3 scale = glm::dvec3(c_sunRadius);
	Sun->GetTransform()->SetScale(scale);
	Sun->SetCollider(physics->CreateCollider(Sphere, Sun));
	//mass
	std::shared_ptr<SphereCollider> sC = std::static_pointer_cast<SphereCollider>(Sun->GetCollider());
	sC->m_mass = c_SunMass;
	Sun->m_CameraDistanceRadius = c_sunRadius * Sun->GetTransform()->GetRenderScale() * 2;
	////////////////////////////////////////////////////////
	
	/* E A R T H */
	std::shared_ptr<Entity> earth = EntityManager->CreateEntity();
	earth->GetTransform()->m_parent = nullptr;
	earth->GetTransform()->m_localPos = c_EarthStartPos;
	earth->m_isSatellite = true;
	earth->SetCollider(physics->CreateCollider(Sphere, earth));
	earth->SetName("Tellus");
	earth->GetTransform()->m_stellartype = PLANET;


	

	
	std::shared_ptr<SphereCollider> cE = std::static_pointer_cast<SphereCollider>(earth->GetCollider());
	

	//textures
	earth->SetDiffuseMap(engine.GetTextureManager()->LoadTexture(".\\Texture\\8k_earth_daymap.jpg", Diffuse));
	earth->SetSpecularMap(engine.GetTextureManager()->LoadTexture(".\\Texture\\8k_earth_specular_map.jpg", Specular));
	earth->SetMesh(engine.GetMeshMangr()->GetMeshByName("sphere2"));
	


	//radius
	double radius = c_EarthRadius;
	scale = glm::dvec3(radius);
	earth->GetTransform()->SetScale(scale);
	earth->m_CameraDistanceRadius = radius * earth->GetTransform()->GetRenderScale() * 2;

	//MASS
	std::shared_ptr<SphereCollider> eC = std::static_pointer_cast<SphereCollider>(earth->GetCollider());
	eC->m_mass = c_EarthMass;
	eC->m_velocity = CircularOrbitVelocity(Sun, AU, c_SunMass) * vDir;
	eC->m_rotationState = stateEarth;

	eC->m_trail->m_color = glm::vec3(0.43f, 0.63f, 0.18f);

	////////////////////////////////////////////////////////


	/* M O O N */
	std::shared_ptr<Entity> moon = EntityManager->CreateEntity();
	moon->GetTransform()->m_parent = nullptr;
	moon->GetTransform()->m_localPos = c_MoonStartPos;
	moon->m_isSatellite = true;

	moon->SetCollider(physics->CreateCollider(Sphere, moon));
	//moon->GetTransform()->SetPos(glm::vec3(3.0f, 0.f, 0.0f));
	moon->SetName("Luna");
	
	moon->GetTransform()->m_stellartype = PLANET;
	//moon->GetTransform()->SetPos(c_MoonStartPos);

	moon->SetDiffuseMap(engine.GetTextureManager()->LoadTexture(".\\Texture\\8k_moon.jpg", Diffuse));
	moon->SetMesh(engine.GetMeshMangr()->GetMeshByName("sphere2"));

	//radius
	scale = glm::dvec3(c_MoonRadius);
	moon->GetTransform()->SetScale(scale);

	//mass
	std::shared_ptr<SphereCollider> mC = std::static_pointer_cast<SphereCollider>(moon->GetCollider());
	mC->m_mass = c_MoonMass;
	mC->m_trail->m_color = glm::vec3(0.7f, 0.7f, 0.7f);
	


	//two-body initialization MOON + EARTH BARYCENTRIC ORBIT
	double ahh = G * (c_EarthMass + c_MoonMass);
	double ahhhh = glm::sqrt(ahh / glm::length(distMoon));

	glm::dvec3 veltest = ahhhh * lunarDir;


	double massTotal = c_EarthMass + c_MoonMass;
	double v_rel_mag = glm::sqrt(G * massTotal / glm::length(distMoon));
	double v_moon_orb = v_rel_mag * (c_EarthMass / massTotal);
	double v_earth_orb = v_rel_mag * (c_MoonMass / massTotal);

	// 2. Calculate the velocity of the BARYCENTER around the Sun
	// The barycenter is slightly further out than the Earth's center
	double r_bary = AU + c_MoonsOffset * (c_MoonMass / massTotal);
	double sunAngularVel = CircularOrbitVelocity(Sun, r_bary, c_SunMass) / r_bary;

	// Notice we use the SAME barycenter velocity for both bodies!
	glm::dvec3 barycenterVel = (sunAngularVel * r_bary) * vDir;

	// 3. Apply the combined velocities
	eC->m_velocity = barycenterVel - (v_earth_orb * lunarDir);
	mC->m_velocity = barycenterVel + (v_moon_orb * lunarDir);

	// Earth is relative to the Sun, so its local velocity is just its orbit around the Sun:
	//eC->m_velocity = CircularOrbitVelocity(Sun, AU, c_SunMass) * vDir;

	// Moon is relative to Earth, so its local velocity is just its orbit around the Earth:
	//mC->m_velocity = CircularOrbitVelocity(earth, c_MoonsOffset, c_EarthMass) * lunarDir;
	std::cout << ahhhh << " <- moon velocity" << std::endl;
	////////////////////////////////////////////////////////



	/* M O O N    R O T A T I O N*/

	stateMoon.orientation = glm::dquat(1, 0, 0, 0);
	stateMoon.angularSpeed = ahhhh / glm::length(distMoon);
	stateMoon.axis = lunarNormal;

	mC->m_rotationState = stateMoon;
	sC->m_rotationState = stateMoon;







	// Energy conservation - The momentum of each center of mass needs to cancel out, or drifting will occur and break stability.

	// P = M * V

	
	glm::dvec3 P = c_SunMass * sC->m_velocity + c_EarthMass * eC->m_velocity + c_MoonMass * mC->m_velocity; // total momentum of system kg*m/s

	double mAll = c_SunMass + c_EarthMass + c_MoonMass; //total mass

	glm::dvec3 velocityCorrection = P / mAll;

	sC->m_velocity -= velocityCorrection;
	eC->m_velocity -= velocityCorrection;
	mC->m_velocity -= velocityCorrection;
	


	
	
	engine.GetCam()->SetOrbitalTarget(eC->m_transform, 200, earth->GetName()->c_str());




	/*
	std::shared_ptr<Entity> test1 = EntityManager->CreateEntity();
	std::shared_ptr<Entity> test12 = EntityManager->CreateEntity();
	std::shared_ptr<Entity> test3 = EntityManager->CreateEntity();
	std::shared_ptr<Entity> test34 = EntityManager->CreateEntity();
	*/









	std::shared_ptr<ObjMessage> msgtest = std::make_shared<ObjMessage>(sphere);
	std::shared_ptr<ObjMessage> msgMonkey = std::make_shared<ObjMessage>(monky);
	engine.GetTextureManager()->LoadTexture(".\\Texture\\th.jpg", Diffuse);
	
	

	//engine.messagequeue.Push(msgMonkey);

	

	std::shared_ptr<Mesh> meshref = engine.manager->GetMesh(crate.c_str());

	
	//test->GetTransform()->AddVelocity(glm::vec3(4.0f, 0.f, 0.f));


	//engine.GetMeshMangr()->AddMesh(crate.c_str(), HertzEngine::DefaultShader);
	//engine.GetMeshMangr()->AddMesh(monky.c_str(), HertzEngine::DefaultShader);
	
	bool hasEnabledTrails = false;
	float time = 0;

	std::shared_ptr<Camera> camref = engine.GetCam();
	camref->fCamSpeed = 200.0;
	//camref->vPos.x = 150000;

	/* */
	bool debugInitialized = false;

	glm::dvec3 P0;     //init total momentum



	//DATA FOR IMGUI


	AstronomicalData earthData	= AstronomicalData(earth, Sun);
	AstronomicalData moonData	= AstronomicalData(moon, earth);
	AstronomicalData sunData	= AstronomicalData(Sun);
	
	auto UIRef = engine.GetEditor();

	UIRef->data.push_back(earthData);
	UIRef->data.push_back(moonData);
	UIRef->data.push_back(sunData);


	while (!engine.bShouldClose)
	{
		//std::cout << engine.bShouldClose << std::endl;
		engine.Update();

		time += HertzEngine::DeltaTime();

		//physics->RayCast(camref->vPos, camref->vFront);


		
		earthData.UpdateData();
		moonData.UpdateData();
		sunData.UpdateData();
			if (time >= 7)
			{
				glm::dvec3 posE = earth->GetTransform()->GetWorldPos();
				glm::dvec3 posM = moon->GetTransform()->GetWorldPos();

				glm::dvec3 velE = eC->m_velocity;
				glm::dvec3 velM = mC->m_velocity;

				double distEM = glm::distance(posE, posM);
				glm::dvec3 relVel = velM - velE;
				double specificEnergy = (0.5 * glm::dot(relVel, relVel)) - (G * c_EarthMass / distEM);

				static double maxOffset = -1e30;
				static double minOffset = 1e30;

				double currentOffset = distEM - c_MoonsOffset;

				if (currentOffset > maxOffset) maxOffset = currentOffset;
				if (currentOffset < minOffset) minOffset = currentOffset;

				std::cout << "\n--- LUNAR OSCILLATION DEBUG ---" << std::endl;
				std::cout << "Specific Energy: " << std::scientific << std::setprecision(4) << specificEnergy << " J/kg" << std::endl;
				std::cout << "Current Offset:  " << std::fixed << std::setprecision(2) << currentOffset << " m" << std::endl;
				std::cout << "Orbit Bounds:    [" << minOffset << " m <---> " << maxOffset << " m]" << std::endl;
				std::cout << "-------------------------------" << std::endl;

				time = 0;
			}


		if (time >= 10 && debugInitialized)
		{

		
		}

		if (!hasEnabledTrails && time >= 6)
		{
			
			mC->m_trail->isUpdating = true;
			eC->m_trail->isUpdating = true;
			mC->m_trail->m_col = mC.get();
			eC->m_trail->m_col = eC.get();
			

			hasEnabledTrails = true;
		}

		/*
		if (time >= 2.0f && test->GetMesh() == nullptr)
		{
			test->SetMesh(engine.manager->GetMesh(crate.c_str()));

			
		}
		*/
	}
	engine.GetMeshMangr()->SaveDataMesh(nullptr);
}



