#pragma once
#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <iostream>
#include "HertzTexture.h"
#include "../Dependencies/glm/glm.hpp"

class Mesh;

struct Vertex
{
	glm::vec3 vPos;
	glm::vec2 vTexCoords;
	glm::vec3 vNormal;
	
};

struct ObjData
{
	std::vector<glm::vec3> vPos;
	std::vector<glm::vec2> vTexCoords;
	std::vector<glm::vec3> vNormal;

	std::vector<unsigned int> indicies;
	std::vector<unsigned int> vPosIndices;
	std::vector<unsigned int> vTexCoordIndices;
	std::vector<unsigned int> vNormalIndices;
};


class ObjLoader
{
private:
	
public:
	std::vector<HertzTexture*> defaultTextures;

	static Mesh* LoadObjData(const char* aPath);

	static std::vector<HertzTexture*> GetDefaultTextures();

	bool LoadOBJ(
		const char* aPath,
		std::vector<glm::vec3>& outVerticies,
		std::vector<glm::vec3>& outUVs,
		std::vector <glm::vec3>& outNormals
	);

	ObjLoader();
	Mesh* LoadObj(const char* aPath);
		

};

#endif