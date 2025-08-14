#include "Meshmanager.h"
#include "ObjLoader.h"
#include "HertzEngine.h"
#include "../Objects/VirtualObject.h"

Meshmanager::Meshmanager()
{
	this->MeshList = {};
	this->MeshCount = 0;
}

void Meshmanager::AddMesh(const char* tPath)
{
	for (Mesh* m : MeshList)
	{
		if (tPath == m->path)
		{
			std::cout << "Mesh at: " << tPath << "already exists." << std::endl;
			break;
		}
	}

	Mesh* mesh = ObjLoader::LoadObjData(tPath);
	MeshList.push_back(mesh);
	MeshCount++;
	 
}

Mesh* Meshmanager::AddMesh(const char* tPath, Shader* shader)
{
	std::cout << tPath << std::endl;

	for (Mesh* m : MeshList)
	{
		if (std::string(tPath) == m->path)
		{
			std::cout << "Mesh at: " << tPath << "already exists." << std::endl;
			return m;
		}
	}
	Mesh* mesh = ObjLoader::LoadObjData(tPath);
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

void Meshmanager::RemoveMesh(Mesh *mDelete)
{
	auto end = MeshList.end();
	std::string path = mDelete->path;

	for (auto it = MeshList.begin(); it != end; it++)
	{
		if (*it == mDelete)
		{
			delete *it;
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
	for (Mesh* mesh : MeshList)
	{

		Shader* temp = mesh->getShader();
		mesh->transform->UpdateModel(temp);
		mesh->Render();

	}
}

Mesh* Meshmanager::GetMesh(const char* tPath)
{
	for (Mesh* m : MeshList)
	{
		if (m->path == tPath)
		{
			return m;
		}
	}
	std::cerr << "Could not find mesh with path: " << tPath << std::endl;

}
