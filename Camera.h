#pragma once
#include "../Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"

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

	glm::vec3 vPos;
	glm::vec3 vFront;
	glm::vec3 vUp;
	glm::vec3 vRight;
	glm::vec3 vWorldUp;

	glm::mat4 projection;

	//euler
	float fYaw;
	float fPitch;


	float fCamSpeed;
	float fMouseSensitivity;
	float fZoom;

	float fprevX;
	float fprevY;

	Camera(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f), glm::vec3 up = glm::vec3(0.f, 1.0f, 0.f), float yaw = fYAW, float pitch = fPITCH);


	void CameraInput(CameraMove dir, float deltaTime);
	void CameraUpdate();
	void MouseMovement(float xOffset, float yOffset);
	void CameraScroll(float value);
	glm::mat4 GetProjection();
	glm::mat4 GetViewMat4();
};

