#pragma once
#include "../Objects/VirtualObject.h"
#include "../Camera.h"


class Camera;
class Entity : public VirtualObject
{
	using TexturePtr = std::shared_ptr<HertzTexture>;

public:

	Entity();

	void Update(double DeltaTime, std::shared_ptr<Camera> m_origin);
	float GetVelocity();

	bool m_isSatellite = false;
	float m_CameraDistanceRadius = 10.f;

};

