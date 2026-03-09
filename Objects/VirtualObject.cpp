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
		
		if (!this->GetTextures().empty())
		{
			mesh->SetTextures(this->GetTextures());
		}
		else
		{
			std::vector<TexturePtr> tex = mesh->textures;
			this->SetTextures(mesh->textures);


			
		}


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

	for (auto& tex : newtextures)
	{
		switch (tex->m_texturetype)
		{
		case Diffuse:
			SetDiffuseMap(tex);
			break;

		case Specular:
			SetSpecularMap(tex);
			break;
		}
	}

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

std::shared_ptr<HertzTexture> VirtualObject::GetDiffuseMap()
{
	if (m_diffuseMap)
	{
		return this->m_diffuseMap;
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<HertzTexture> VirtualObject::GetSpecularMap()
{
	if (m_SpecularMap)
	{
		return this->m_SpecularMap;
	}
	else
	{
		return nullptr;
	}
}

void VirtualObject::ClearMesh()
{
	if (m_mesh)
	{
		m_mesh = nullptr;

		/*
		m_mesh->transform = std::make_shared<Transform>();
		m_mesh->parent = nullptr;
		this->m_shader = nullptr;
		this->m_mesh = nullptr;
		*/
	}
}

void VirtualObject::UpdateTextureTypes()
{
	
	std::vector<TexturePtr> newTextures;

	if (m_diffuseMap)
	{
		m_diffuseMap->m_type = Diffuse;
		newTextures.push_back(this->m_diffuseMap);
	}
	if (m_SpecularMap)
	{
		newTextures.push_back(this->m_SpecularMap);
		m_SpecularMap->m_texturetype = Specular;
	}

	if (!newTextures.empty())
	{
		this->m_textures = newTextures;
	}

}

void VirtualObject::SetDiffuseMap(std::shared_ptr<HertzTexture> newmap)
{
	this->m_diffuseMap = newmap;
	UpdateTextureTypes();

}

void VirtualObject::SetSpecularMap(std::shared_ptr<HertzTexture> newmap)
{
	this->m_SpecularMap = newmap;
	UpdateTextureTypes();
}

std::shared_ptr<Collider> VirtualObject::GetCollider()
{
	if (m_Collider)
	{
		return this->m_Collider;
	}
	else
	{
		return nullptr;
	}
}

void VirtualObject::SetCollider(std::shared_ptr<Collider> toSet)
{
	this->m_Collider = toSet;

}



void VirtualObject::GenID()
{
	std::string temp = "Unnamed ";
	std::string actualID = temp.append(std::to_string(ID));
	std::cout << actualID << std::endl;

	ID++;
}


