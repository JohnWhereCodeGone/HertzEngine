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
	std::vector<std::shared_ptr<HertzTexture>> defaultTextures;

	static std::shared_ptr<Mesh> LoadObjData(const char* aPath);
	static std::shared_ptr<ObjData> GetObjData(const char* aPath);

	static std::vector<std::shared_ptr<HertzTexture>> GetDefaultTextures();

	bool LoadOBJ(
		const char* aPath,
		std::vector<glm::vec3>& outVerticies,
		std::vector<glm::vec3>& outUVs,
		std::vector <glm::vec3>& outNormals
	);

	ObjLoader();
	//static std::shared_ptr<Mesh> LoadObj(const char* aPath);
		

};

#endif