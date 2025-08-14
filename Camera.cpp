#include "Camera.h"

void Camera::CameraUpdate()
{
	glm::vec3 front = {};
	front.x = cos(glm::radians(fYaw)) * cos(glm::radians(fPitch));
	front.y = sin(glm::radians(fPitch));
	front.z = sin(glm::radians(fYaw)) * cos(glm::radians(fPitch));
	vFront = glm::normalize(front);
	vRight = glm::normalize(glm::cross(vFront, vWorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	vUp = glm::normalize(glm::cross(vRight, vFront));
}
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : vFront(glm::vec3(0.f, 0.f, -1.f)), fCamSpeed(fSPEED), fMouseSensitivity(fSENSITIVITY), fZoom(fZOOM)
{


	vPos = position;
	vWorldUp = up;
	fYaw = yaw;
	fPitch = pitch;

	projection = glm::mat4(1.0f);
	CameraUpdate();
}
void Camera::CameraScroll(float value)
{
	fCamSpeed += value / 2;
	
}

glm::mat4 Camera::GetProjection()
{
	return this->projection;
}

void Camera::CameraInput(CameraMove dir, float deltaTime)
{
	float displacement = fCamSpeed * deltaTime;

	if (dir == FORWARD)
	{
		vPos += vFront * displacement;
	}
	if (dir == BACK)
	{
		vPos -= vFront * displacement;
	}
	if (dir == LEFT)
	{
		vPos -= vRight * displacement;
	}
	if (dir == RIGHT)
	{
		vPos += vRight * displacement;
	}
	if (dir == UP)
	{
		vPos += vUp * displacement;
	}
	if (dir == DOWN)
	{
		vPos -= vUp * displacement;
	}
}


void Camera::MouseMovement(float xOffset, float yOffset)
{
	xOffset *= fMouseSensitivity;
	yOffset *= fMouseSensitivity;

	fYaw += xOffset;
	fPitch += yOffset;

	if (fPitch > 89.f)
	{
		fPitch = 89.f;
	}
	if (fPitch < -89.f)
	{
		fPitch = -89.f;
	}


	CameraUpdate();
}


glm::mat4 Camera::GetViewMat4()
{
	return glm::lookAt(vPos, vPos + vFront, vUp);
}
