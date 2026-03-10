#include "Camera.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "../Lights/Spotlight.h"
#include "../glm/gtx/string_cast.hpp"

void Camera::CameraUpdate()
{

	glm::vec3 front = {};
	if (m_LookAt)   //Orbital cam
	{

		glm::dvec3 tarPos = m_LookAt->GetPos();
		if (m_LookAt->m_stellartype != 0)
		{


			tarPos = glm::mix(vPos, m_LookAt->GetVisualPos(), 0.7);
		}

		constexpr double limit = glm::radians(89.9f);
		m_latitude = glm::clamp(m_latitude, -limit, limit);
			
		
		vPos.x = tarPos.x + m_distance * cos(m_latitude) * cos(m_longitude);
		vPos.y = tarPos.y + m_distance * sin(m_latitude);
		vPos.z = tarPos.z + m_distance * cos(m_latitude) * sin(m_longitude);

		
		vFront = glm::normalize(tarPos - vPos);


	}

	else
	{

		front.x = cos(glm::radians(fYaw)) * cos(glm::radians(fPitch));
		front.y = sin(glm::radians(fPitch));
		front.z = sin(glm::radians(fYaw)) * cos(glm::radians(fPitch));
		vFront = glm::normalize(front);
	}

	vRight = glm::normalize(glm::cross(vFront, vWorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	vUp = glm::normalize(glm::cross(vRight, vFront));

	if (m_cameralight)
	{
		/*
		m_cameralight->GetProperties().LightDir = vFront;
		m_cameralight->GetTrans()->SetPos(vPos);
		m_cameralight->GetShouldLight() = m_lightIsOn;
		*/

	}

	

}
Camera::Camera(std::shared_ptr<Spotlight> light, glm::vec3 position, glm::vec3 up, float yaw, float pitch) : vFront(glm::vec3(0.f, 0.f, -1.f)), fCamSpeed(fSPEED), fMouseSensitivity(fSENSITIVITY), fZoom(fZOOM), m_cameralight(light)
{


	vPos = position;
	vWorldUp = up;
	fYaw = yaw;
	fPitch = pitch;
	m_lightIsOn = false;

	m_LookAtName = " ";
	/*
	front.x = cos(glm::radians(fYaw)) * cos(glm::radians(fPitch));
	front.y = sin(glm::radians(fPitch));
	front.z = sin(glm::radians(fYaw)) * cos(glm::radians(fPitch));
	*/

	this->m_takesInput = true;

	if (light)
	{
		light->m_ID = "CAMERA SPOTLIGHT";
	}
	
	//m_cameralight->m_ID = "Camera Spot Light";
	projection = glm::mat4(1.0f);
	m_LookAt = nullptr;
	CameraUpdate();
}
void Camera::CameraScroll(float value)
{

	// Currently Disabled
	if (m_LookAt && m_LookAt->m_stellartype != 0)
	{
		m_distance += value * 10000000;
		return;
	}
	fCamSpeed += value / 2;
	
}

void Camera::SetOrbitalTarget(std::shared_ptr<Transform> target, double distance, std::string name)
{


	if (target)
	{
		m_LookAt = target;
	}
	double initdist = glm::length(m_LookAt->GetScale()) * m_LookAt->GetRenderScale();
	m_minDist = initdist * 3.141f; //diameter = 2x r, + offset;
	m_distance = initdist * 10.5f;
	
	m_LookAtName = name;

	//transition

	//TODO fix zooming +

}

glm::mat4 Camera::GetProjection() const
{
	return glm::perspective(glm::radians(fZoom), 1920.f / 1080.f, 0.1f, 500000.f);
	//return this->projection;
}

void Camera::CameraInput(CameraMove dir, float deltaTime)
{
	if (!m_takesInput)
	{
		return;
	}
	double displacement = fCamSpeed * deltaTime * 0.01;

	/*
	if (m_LookAt)
	{
		if (dir == FORWARD)
		{
			m_latitude += displacement;
		}
		if (dir == BACK)
		{
			m_latitude -= displacement;
		}
		if (dir == LEFT)
		{
			m_longitude += displacement;
		}
		if (dir == RIGHT)
		{
			m_longitude -= displacement;
		}
		if (dir == UP)
		{
			m_distance += displacement;
		}
		if (dir == DOWN)
		{
			m_distance -= displacement;

		}

		
	}
	*/

	
	if (m_LookAt)
	{
		
		if (dir == FORWARD)
		{
			if (m_distance >= m_minDist)
			{
				float Delta = 100 * deltaTime;

				m_distance -= Delta;
			}
		}
		if (dir == BACK)
		{
			if (m_distance <= 1000)
			{
				float Delta = 100 * deltaTime;

				m_distance += Delta;
			}
		}

	}
	else
	{
		if (dir == FORWARD)
		{
			vPos += vFront * displacement;
		}
		if (dir == BACK)
		{
			vPos -= vFront * displacement;
		}

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
	CameraUpdate();
}


void Camera::MouseMovement(float xOffset, float yOffset)
{
	/*
	if (m_LookAt)
	{
		CameraUpdate();
		return;
	}
	*/
	if (!m_takesInput)
	{
		return;
	}
	xOffset *= fMouseSensitivity;
	yOffset *= fMouseSensitivity;


	constexpr float orbitalCamSense = 1.f / 3.f;

	m_longitude += xOffset * orbitalCamSense;
	m_latitude += yOffset * orbitalCamSense;

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

std::string Camera::GetLookAtName()
{
	return this->m_LookAtName;
}

