#pragma once
#include <iostream>
#include <vector>
#include "../Mesh.h"
#include <unordered_map>
#include <TextureManager.h>
#include <memory>
#include "../Serializer/Serializer.h"

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
	using ShaderPtr = std::shared_ptr<Shader>;

	Meshmanager();
	static std::vector<std::shared_ptr<HertzTexture>> GetDefaultTextures();
	std::shared_ptr<Mesh> AddMeshByData(std::shared_ptr<ObjData> data, const char* name = nullptr, ShaderPtr shader = nullptr);
	std::shared_ptr<Mesh> AddMesh(const char* tPath, ShaderPtr shader = nullptr);
	void AddMesh(const char* tPath);
	bool AddMesh(std::shared_ptr<Mesh> meshToAdd);
	void RemoveMesh(std::shared_ptr<Mesh> mDelete);
	void Render();

	void SaveDataMesh(std::shared_ptr<Mesh> meshToSave);
	void LoadDataMesh();

	std::shared_ptr<Mesh> GetMesh(const char* tPath);
	int MeshCount;

protected:

	std::vector<std::shared_ptr<Mesh>> MeshList;
	std::unordered_map<MeshKey, Mesh*, MeshKeyHash> meshMap;
	TextureManager m_texman;
};

