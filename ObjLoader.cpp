#include "ObjLoader.h"
#include <unordered_map>
#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>


// Problem: passing the indicies to EBO,
// Structure: loadobj returns a mesh initialized with local function variables. 
// PROBLEM: Currently the obj file can be in any order. In order to.




ObjLoader::ObjLoader()
{
	{

		//set up default textures

	}
}

Mesh* ObjLoader::LoadObj(const char* aPath)
{
	return nullptr;
}

Mesh* ObjLoader::LoadObjData(const char* aPath)
{
	ObjData data;

	std::ifstream file(aPath);
	if (!file.is_open()) {
		std::cerr << "Failed to open OBJ file: " << aPath << std::endl;
		return nullptr;
	}

	std::string line, prefix;
	

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		iss >> prefix;

		if (prefix == "v")
		{
			glm::vec3 pos;
			iss >> pos.x >> pos.y >> pos.z;
			data.vPos.push_back(pos);
		}
		else if (prefix == "vn")
		{
			glm::vec3 norm;
			iss >> norm.x >> norm.y >> norm.z;
			data.vNormal.push_back(norm);
		}
		else if (prefix == "vt")
		{
			glm::vec2 texcoords;
			iss >> texcoords.x >> texcoords.y;
			data.vTexCoords.push_back(texcoords);
			std::cout << "hey" << std::endl;
		}
		else if (prefix == "f")
		{
			std::string vertexData;
			for (int i = 0; i < 3; i++)
			{
				iss >> vertexData;
				std::replace(vertexData.begin(), vertexData.end(), '/', ' ');
				std::istringstream viss(vertexData);
				int vIndex = 0, tIndex = 0, nIndex = 0;
				viss >> vIndex;
				if (viss.peek() == ' ') viss >> tIndex;
				if (viss.peek() == ' ') viss >> nIndex;
				data.vPosIndices.push_back(vIndex - 1);
				if (tIndex > 0) data.vTexCoordIndices.push_back(tIndex - 1);
				if (nIndex > 0) data.vNormalIndices.push_back(nIndex - 1);
			}
		}
	}

	//debug

	//std::cout << "Vertices read: " << data.vPos.size() << std::endl;
	//std::cout << "Normals read: " << data.vNormal.size() << std::endl;
	//std::cout << "TexCoords read: " << data.vTexCoords.size() << std::endl;
	//std::cout << "Vertex Indices read: " << data.vPosIndices.size() << std::endl;
	//std::cout << "TexCoord Indices read: " << data.vTexCoordIndices.size() << std::endl;
	//std::cout << "TEX COORDS READ: " << std::endl;
	//for (size_t i = 0; i < data.vTexCoords.size(); ++i)
	//{
	//	//std::cout << data.vTexCoords[i].x << " " <<  data.vTexCoords[i].y << std::endl;
	//}

	if (data.vPos.size() <= 0)
	{
		std::cerr << "ERROR FAILED TO READ VERTICES: " << aPath << std::endl;
		return nullptr;
	}

	file.close();
	std::cout << "Loaded Mesh from path: " << aPath << std::endl;
	return new Mesh(data, GetDefaultTextures(), aPath);
	
}

std::vector<HertzTexture*> ObjLoader::GetDefaultTextures()
{

	std::vector<HertzTexture*> textures;
	HertzTexture* diffuse = new HertzTexture("./texture/container2.png", true);
	HertzTexture* specular = new HertzTexture("./texture/container2_specular.png", true);


	diffuse->type = "texture_diffuse";
	specular->type = "texture_specular";

	diffuse->texturetype = TextureType::Diffuse;
	specular->texturetype = TextureType::Specular;

	textures.push_back(diffuse);
	textures.push_back(specular);

	return textures;
}


