#pragma once
#include <queue>
#include <iostream>
#include "../glm/glm.hpp"
#include "../Shaders/HertzShader.h"
#include "../Transform.h"

// Get Shader Set up
// Get Rendering Set up
// Render before physics loop and after entities/meshes

constexpr int MAX_POINTS = 2000;


class Trail
{
	


public:
	Trail(std::shared_ptr<Transform> t, std::shared_ptr<Shader> shad = nullptr);

	std::deque<glm::dvec3>	m_points;
	std::shared_ptr<Shader> m_shad;

	int		m_maxPoints		= 2000;
	double	m_Accumulator	= 0;

	//rendering
	std::vector<glm::vec3> m_vertices;

	unsigned int VBO;
	
	unsigned int VAO;
	bool debug = false;


	std::shared_ptr<Transform> m_trans;
	

	void InitBuffers();
	void Update(double dT);
	void UpdateBuffer();
	void Draw();
};

