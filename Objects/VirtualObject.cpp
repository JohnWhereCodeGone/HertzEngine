#include "VirtualObject.h"
#include "../Mesh.h"
#include "../Transform.h"
#include <HertzShader.h>

int VirtualObject::ID = 0;


//VO -> update transform ptr, shader mesh -> render mesh -> update for next VO -> render...

VirtualObject::VirtualObject()
{

	this->m_transform = std::make_shared<Transform>();

	this->m_name = nullptr;
	this->m_shader = nullptr;
	this->m_mesh = nullptr;


	GenID();
}



bool VirtualObject::SetTransform(TransformPtr trans)
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

bool VirtualObject::SetMesh(MeshPtr mesh)
{
	if (mesh)
	{
		mesh->transform = this->GetTransform();
		mesh->parent = this;
		this->m_shader = mesh->getShader();
		this->m_mesh = mesh;
	}
	else
	{
		return false;
	}
}

bool VirtualObject::SetShader(ShaderPtr shader)
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
	if ( newname.size() > 0 )
		this->m_name = new std::string( newname );
	else
		return;
}

void VirtualObject::SetTextures(const std::vector<std::shared_ptr<HertzTexture>>& newtextures)
{
	this->m_textures = newtextures;
}



const std::vector<std::shared_ptr<HertzTexture>> &VirtualObject::GetTextures()
{
		return this->m_textures;
}

std::shared_ptr<Transform> VirtualObject::GetTransform()
{
	if (m_transform)
		return this->m_transform;
	else
		return nullptr;
}

std::shared_ptr<Shader> VirtualObject::GetShader()
{
	if (m_shader)
		return m_shader;
	else
		return nullptr;
}

std::shared_ptr<Mesh> VirtualObject::GetMesh()
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

void VirtualObject::ClearMesh()
{
	if (m_mesh)
	{
		m_mesh->transform = std::make_shared<Transform>();
		m_mesh->parent = nullptr;
		this->m_shader = nullptr;
		this->m_mesh = nullptr;
	}
}



void VirtualObject::GenID()
{
	std::string temp = "Unnamed ";
	std::string actualID = temp.append(std::to_string(ID));
	std::cout << actualID << std::endl;

	ID++;
}


