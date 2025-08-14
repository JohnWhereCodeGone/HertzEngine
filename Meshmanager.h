#pragma once
#include <iostream>
#include <vector>
#include "Mesh.h"
#include <unordered_map>


class HertzEngine;

struct MeshKey {
	int VAO;
	int VBO;
	int EBO;

	bool operator==(const MeshKey& other) const {
		return VAO == other.VAO &&
			VBO == other.VBO &&
			EBO == other.EBO;
	}
};

// look into turning this into a hash map.
struct MeshKeyHash {
	std::size_t operator()(const MeshKey& k) const {
		return ((std::hash<int>()(k.VAO) ^
			(std::hash<int>()(k.VBO) << 1)) >> 1) ^
			(std::hash<int>()(k.EBO) << 1);
	}
};

class Meshmanager
{
	
public:

	Meshmanager();

	void AddMesh(const char* tPath);
	Mesh* AddMesh(const char* tPath, Shader* shader = nullptr);
	void RemoveMesh(Mesh* mDelete);
	void Render();
	Mesh* GetMesh(const char* tPath);
	int MeshCount;

protected:
	std::vector<Mesh*> MeshList;
	std::unordered_map<MeshKey, Mesh*, MeshKeyHash> meshMap;

};

