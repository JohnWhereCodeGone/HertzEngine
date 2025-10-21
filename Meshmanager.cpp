#include "Meshmanager.h"
#include "ObjLoader.h"
#include "HertzEngine.h"
#include "../Objects/VirtualObject.h"
#include "HertzTexture.h"
#include "TextureManager.h"

Meshmanager::Meshmanager()
{
	this->MeshList = {};
	this->MeshCount = 0;
}

unsigned int id = 0;
void Meshmanager::AddMesh(const char* tPath)
{
	for (std::shared_ptr<Mesh> m : MeshList)
	{
		if (tPath == m->path)
		{
			std::cout << "Mesh at: " << tPath << "already exists." << std::endl;
			break;
		}
	}

	std::shared_ptr<Mesh> mesh = ObjLoader::LoadObjData(tPath);
	MeshList.push_back(mesh);
	MeshCount++;
	 
}

std::shared_ptr<Mesh> Meshmanager::AddMesh(const char* tPath, ShaderPtr shader) //this is the real one, delete the others.
{
	std::cout << tPath << std::endl;

	for (std::shared_ptr<Mesh> m : MeshList)
	{
		if (std::string(tPath) == m->path)
		{
			std::cout << "Mesh at: " << tPath << "already exists." << std::endl;
			return m;
		}
	}
	std::shared_ptr<Mesh> mesh = ObjLoader::LoadObjData(tPath);
	if (!mesh)
	{
		std::cerr << "MeshManager: LoadObjData returned nullptr mesh at - " << tPath << std::endl;
	}

	if (!shader)
	{
		shader = HertzEngine::GetDefaultShader();
	}

	mesh->setShader(shader);
	MeshList.push_back(mesh);
	MeshCount++;
	
	if (mesh)
	{
		mesh->path = tPath;
		return mesh;

	}
	else
		return nullptr;

}

std::shared_ptr<Mesh> Meshmanager::AddMeshByData(std::shared_ptr<ObjData> data, const char* name, ShaderPtr shader)
{
	
	if (!data)
	{
		std::cerr << "MeshManager: LoadObjData returned nullptr mesh at - " << "X" << std::endl;
		return nullptr;
	}
	std::shared_ptr<Mesh> newMesh = std::make_shared<Mesh>(*data, HertzEngine::GetDefaultTexture(), nullptr);

	if (!shader)
	{
		
	}
	std::shared_ptr<Shader> newShad = HertzEngine::GetDefaultShader();

	newMesh->setShader(newShad);
	MeshList.push_back(newMesh);
	MeshCount++;

	if (newMesh)
	{
		newMesh->path = name;
		id++;
		return newMesh;

	}
	else
		return nullptr;
	
	
}



bool Meshmanager::AddMesh(std::shared_ptr<Mesh> meshToAdd)
{
	// doesn't check for duplicate meshes, doesn't adjust tPath, but fuck it, multithreading.

	if (!meshToAdd)
	{
		std::cerr << "MeshManager: Failed to add mesh from raw ptr" << std::endl;
		return false;
	}

	if (!meshToAdd->getShader())
	{
		meshToAdd->setShader(HertzEngine::GetDefaultShader());
	}

	if (meshToAdd)
	{
		MeshList.push_back(meshToAdd);
		MeshCount++;
		return true;

	}
	else
	{
		return false;

	}
	return false; //tf
}

void Meshmanager::RemoveMesh(std::shared_ptr<Mesh> mDelete)
{
	auto end = MeshList.end();
	std::string path = mDelete->path;

	for (auto it = MeshList.begin(); it != end; it++)
	{
		if (*it == mDelete)
		{
			MeshList.erase(it);
			MeshCount--;
			std::cout << "Deleted mesh from: " << path << std::endl;
			return;
		}
	}

	std::cerr << "Mesh manager: Error! Failed to delete mesh" << std::endl;
	
}

void Meshmanager::Render()
{
	if (MeshList.empty())
		return;
	for (std::shared_ptr<Mesh> mesh : MeshList)
	{

		ShaderPtr temp = mesh->getShader();
		mesh->transform->UpdateModel(temp);
		mesh->Render();

	}
}

std::shared_ptr<Mesh> Meshmanager::GetMesh(const char* tPath)
{
	for (std::shared_ptr<Mesh> m : MeshList)
	{
		if (m->path == tPath)
		{
			return m;
		}
	}
	std::cerr << "Could not find mesh with path: " << tPath << std::endl;
	return nullptr;
}

std::vector<std::shared_ptr<HertzTexture>> Meshmanager::GetDefaultTextures()
{
	std::vector<std::shared_ptr<HertzTexture>> textures;
	std::shared_ptr<HertzTexture> diffuse = std::make_shared<HertzTexture>("./texture./container2.png", true);
	std::shared_ptr<HertzTexture> specular = std::make_shared<HertzTexture>("./texture/container2_specular.png", true);


	diffuse->m_type = "texture_diffuse";
	specular->m_type = "texture_specular";

	diffuse->m_texturetype = TextureType::Diffuse;
	specular->m_texturetype = TextureType::Specular;

	textures.push_back( diffuse );
	textures.push_back(specular);

	return textures;
}


