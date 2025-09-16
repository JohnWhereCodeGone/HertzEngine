#include "Meshmanager.h"
#include "ObjLoader.h"
#include "HertzEngine.h"
#include "../Objects/VirtualObject.h"
#include "HertzTexture.h"

Meshmanager::Meshmanager()
{
	this->MeshList = {};
	this->MeshCount = 0;
}


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

std::shared_ptr<Mesh> Meshmanager::AddMesh(const char* tPath, Shader* shader) //this is the real one, delete the others.
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

std::shared_ptr<Mesh> Meshmanager::AddMeshByData(std::shared_ptr<ObjData> data, Shader* shader)
{
	
	if (!data)
	{
		std::cerr << "MeshManager: LoadObjData returned nullptr mesh at - " << "X" << std::endl;
		return nullptr;
	}
	std::shared_ptr<Mesh> newMesh = std::make_shared<Mesh>(*data, GetDefaultTextures(), nullptr);

	if (!shader)
	{
		shader = HertzEngine::GetDefaultShader();
	}

	newMesh->setShader(shader);
	MeshList.push_back(newMesh);
	MeshCount++;

	if (newMesh)
	{
		newMesh->path = "undefined";
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

		Shader* temp = mesh->getShader();
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

}

std::vector<HertzTexture*> Meshmanager::GetDefaultTextures()
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


