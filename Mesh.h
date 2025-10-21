#pragma once

#include <iostream>
#include <vector>
#include "../Dependencies/glm/glm.hpp"
#include "./Dependencies/glm/gtc/matrix_transform.hpp"
#include "./Dependencies/glm/gtc/type_ptr.hpp"
#include "Shaders/HertzShader.h"
#include "HertzTexture.h"
#include "Transform.h"
#include "ObjLoader.h"

#include "Component.h"

class Component;



struct VertexKey {
	int posIndex;
	int texCoordIndex;
	int normalIndex;

	bool operator==(const VertexKey& other) const {
		return posIndex == other.posIndex &&
			texCoordIndex == other.texCoordIndex &&
			normalIndex == other.normalIndex;
	}
};

// ^ is a XOR bit operator, and << shifts it 1 bit to the left. avoids duplication of keys, look into this more.
struct VertexKeyHash {
	std::size_t operator()(const VertexKey& k) const {
		return ((std::hash<int>()(k.posIndex) ^
			(std::hash<int>()(k.texCoordIndex) << 1)) >> 1) ^
			(std::hash<int>()(k.normalIndex) << 1);
	}
};


class Mesh : public Component
{

private:
	
	using ShaderPtr = std::shared_ptr<Shader>;
	unsigned int VAO;
	unsigned int EBO;
	unsigned int VBO;
	ShaderPtr shader;
	int indiciesSize;

	
public:
	void Attach(VirtualObject& obj) override;
	std::shared_ptr<Transform> transform;
	std::vector<Vertex>	vertices;
	std::vector<unsigned int> indicies;
	std::vector<std::shared_ptr<HertzTexture>> textures;

	~Mesh();
	Mesh(const ObjData &data, std::vector<std::shared_ptr<HertzTexture>> textures, const char* tPath = " "); //real

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<HertzTexture>> textures);

	void setShader(ShaderPtr shader);
	ShaderPtr getShader();

	void Draw(Shader& shader);
	void Render();
	//void Draw();
	void SetTextures(std::vector<std::shared_ptr<HertzTexture>> texin);
	void InitMesh();

	std::string path;

	VirtualObject* parent;

	//start sorting after graphics

	// 1. obj loader, 2. mip-map settings, 3. Start with ligths, 4. UI/imgui (if), 5. Shadow Mapping
};

