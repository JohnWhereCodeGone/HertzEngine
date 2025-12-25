#pragma once
#include "Collider.h"
#include "../Transform.h"
#include <queue>

struct Trail
{
	std::deque<glm::dvec3> points;
	
	
	int m_maxPoints = 2000;
	double m_Accumulator = 0;

	//rendering
	std::vector<glm::vec3> verticies;
	unsigned int VBO;
	unsigned int VAO;
	void Init();

	void UpdateBuffer();
	void Draw();

};


class SphereCollider : public Collider
{

public:

	SphereCollider(std::shared_ptr<Entity> parent = nullptr);
	std::shared_ptr<Trail> m_trail;



	double m_Radius;
	float m_BaseRadius;

};

