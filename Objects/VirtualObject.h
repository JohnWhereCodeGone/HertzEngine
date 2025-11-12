#pragma once
#include <iostream>
#include "HertzTexture.h"

class Mesh;
class Shader;
class Transform;

struct Material
{
	float Shine = 261.0f;
};

//update transform -> other components, such as light.
class VirtualObject
{

public:

	using MeshPtr = std::shared_ptr<Mesh>;
	using ShaderPtr = std::shared_ptr<Shader>;
	using TransformPtr = std::shared_ptr<Transform>;
	
	VirtualObject();
	virtual ~VirtualObject() = default;

	bool SetTransform(TransformPtr trans);
	bool SetMesh(MeshPtr mesh);
	bool SetShader(ShaderPtr shader);
	void SetName(const std::string& newname);
	void SetTextures(const std::vector<std::shared_ptr<HertzTexture>>& textures);
	

	const std::vector<std::shared_ptr<HertzTexture>> &GetTextures();
	TransformPtr GetTransform();
	ShaderPtr GetShader();
	MeshPtr GetMesh();
	std::string* GetName();
	void ClearMesh();
	
	
	void GenID();

private:

	TransformPtr m_transform;
	MeshPtr m_mesh;
	ShaderPtr m_shader;

	
	std::vector<std::shared_ptr<HertzTexture>> m_textures;
	std::string* m_name;

	static int ID; 
};


