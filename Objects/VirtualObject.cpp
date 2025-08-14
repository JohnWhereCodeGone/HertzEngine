#include "VirtualObject.h"
#include "../Mesh.h"
#include "../Transform.h"
#include <HertzShader.h>
int VirtualObject::ID = 0;


//VO -> update transform ptr, shader mesh -> render mesh -> update for next VO -> render...

VirtualObject::VirtualObject()
{

	this->m_transform = new Transform;

	this->m_name = nullptr;
	this->m_shader = nullptr;
	this->m_mesh = nullptr;


	GenID();
}



bool VirtualObject::SetTransform(Transform* trans)
{
	if (trans)
	{
		this->m_transform = trans;
	}
	else
	{
		return false;
	}
}

bool VirtualObject::SetMesh(Mesh* mesh)
{
	if (mesh)
	{

		this->m_mesh = mesh;
	}
	else
	{
		return false;
	}
}

bool VirtualObject::SetShader(Shader* shader)
{
	if (shader)
	{
		this->m_shader = shader;
	}
	else
	{
		return false;
	}
}

void VirtualObject::SetName(const std::string& newname)
{
	if (newname.size() > 0)
		this->m_name = new std::string(newname);
	else
		return;
}

void VirtualObject::SetTextures(const std::vector<HertzTexture*>& newtextures)
{
	this->m_textures = newtextures;
}



std::vector<HertzTexture*> VirtualObject::GetTextures()
{
	if (!m_textures.empty())
	{
		return this->m_textures;
	}
}

Transform* VirtualObject::GetTransform()
{
	if (m_transform)
		return m_transform;
	else
		return nullptr;
}

Shader* VirtualObject::GetShader()
{
	if (m_shader)
		return m_shader;
	else
		return nullptr;
}

Mesh* VirtualObject::GetMesh()
{
	if (m_mesh)
		return m_mesh;
	else
		return nullptr;
}

std::string* VirtualObject::GetName()
{
	if (m_name)
		return m_name;
	else
		return nullptr;
}

void VirtualObject::GenID()
{
	std::string temp = "Unnamed ";
	std::string actualID = temp.append(std::to_string(ID));
	std::cout << actualID << std::endl;

	ID++;
}


