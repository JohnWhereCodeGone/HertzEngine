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


class VirtualObject
{

public:

	
	VirtualObject();
	virtual ~VirtualObject() = default;

	bool SetTransform(Transform* trans);
	bool SetMesh(Mesh* mesh);
	bool SetShader(Shader* shader);
	void SetName(const std::string& newname);
	void SetTextures(const std::vector<HertzTexture*>& textures);
	

	std::vector<HertzTexture*> GetTextures();
	Transform* GetTransform();
	Shader* GetShader();
	Mesh* GetMesh();
	std::string* GetName();
	
	
	void GenID();

private:

	Transform* m_transform;
	Mesh* m_mesh;
	Shader* m_shader;

	
	std::vector<HertzTexture*> m_textures;
	std::string* m_name;

	static int ID;
};


