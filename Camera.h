#pragma once
#include "../Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "../Lights/Lightmanager.h"

//seperate transform into seperate class

enum CameraMove
{
	FORWARD,
	BACK,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

const float fYAW = -90.f;
const float fPITCH = 0.f;

const float fSPEED = 2.5f;

const float fSENSITIVITY = 0.05f;
const float fZOOM = 45.f;

class Camera
{
public:

	//Update me for transform


	glm::dvec3 vPos;
	glm::dvec3 vFront;
	glm::dvec3 vUp;
	glm::dvec3 vRight;
	glm::dvec3 vWorldUp;

	glm::mat4 projection;

	//euler
	float fYaw;
	float fPitch;


	float fCamSpeed;
	float fMouseSensitivity;
	float fZoom;

	float fprevX;
	float fprevY;

	bool m_lightIsOn;
	bool m_takesInput;


	glm::dvec3 m_FloatingOrigin;

	//orital camera

	double m_distance	= 0;
	double m_longitude	= 0;
	double m_latitude	= 0;
	double m_minDist		= 0;


	std::string m_LookAtName;

	Camera(std::shared_ptr<Spotlight> light, glm::vec3 position = glm::vec3(0.f, 0.f, 0.f), glm::vec3 up = glm::vec3(0.f, 1.0f, 0.f), float yaw = fYAW, float pitch = fPITCH);


	std::shared_ptr<Spotlight> m_cameralight;

	void CameraInput(CameraMove dir, float deltaTime);
	void CameraUpdate();
	void MouseMovement(float xOffset, float yOffset);
	void CameraScroll(float value);
	void SetOrbitalTarget(std::shared_ptr<Transform> target, double distance = 0, std::string name = " ");

	

	std::shared_ptr<Transform> m_LookAt;
	glm::mat4 GetProjection() const;
	glm::mat4 GetViewMat4();
	std::string GetLookAtName();

	

	
};

