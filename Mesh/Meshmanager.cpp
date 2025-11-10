#include "Meshmanager.h"
#include "../ObjLoader.h"
#include "../HertzEngine.h"
#include "../Objects/VirtualObject.h"
#include "HertzTexture.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include <filesystem>

Meshmanager::Meshmanager()
{
	this->MeshList = {};
	this->MeshCount = 0;

	this->m_meshFilePath = "./Resources/";
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
		newMesh->setShader(HertzEngine::GetDefaultShader());
	}
	

	int xdc = 0;

	std::shared_ptr<Shader> newShad = HertzEngine::GetDefaultShader();

	newMesh->setShader(newShad);
	MeshList.push_back(newMesh);
	MeshCount++;

	if (newMesh)
	{
		newMesh->path = name;
		newMesh->SetName(Serializer::PathToName(std::string(name)));

		std::cout << "MESH NAME IS " << newMesh->GetName() << std::endl;
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

void Meshmanager::SetFilePath(const char* newPath)
{
	this->m_meshFilePath = newPath;
}

const char* Meshmanager::GetFilePath()
{
	return this->m_meshFilePath;
}

void Meshmanager::SaveDataMesh(std::shared_ptr<Mesh> meshToSave)
{
	std::string filePath = m_meshFilePath;
	
	for (auto it = MeshList.begin(); it != MeshList.end(); it++)
	{
		if (*it == nullptr)
			continue;

		//1. create the path name.
		std::shared_ptr<Mesh> toSave = *it;
		
		std::string namePath = filePath;
		namePath += toSave->GetName();
		namePath += ".mesh";

		//create file
		std::ofstream outFile(namePath, std::ios::binary);
		if (!outFile.is_open())
		{
			std::cout << "[MeshManager::SaveDataMesh] Error! Creating .mesh file failed.";
			continue;
		}


		//get the nr of elements ->-> write the nr of elements -> calculate the total byte size of all elements -> write the elements
		
		
		//Indicies

		uint64_t nrOfElements = toSave->indicies.size();
		Serializer::WriteBinaryFileData(outFile, nrOfElements);

		uint64_t elementSizeBytes = nrOfElements * sizeof(toSave->indicies[0]);
		outFile.write(reinterpret_cast<const char*>(toSave->indicies.data()), elementSizeBytes);
		

		//Vertecies

		uint64_t nrOfVertices = toSave->vertices.size();
		Serializer::WriteBinaryFileData(outFile, nrOfVertices);

		uint64_t VerticesSizeBytes = sizeof(Vertex) * nrOfVertices;
		outFile.write(reinterpret_cast<const char*>(toSave->vertices.data()), VerticesSizeBytes);

		//Shader path, texture path:
		//fuck textures / shaders, load and use engine defaults for now.

		std::cout << "Saved mesh: " << filePath << std::endl;

		outFile.close();
	}

	

	//LoadDataMesh();

}

void Meshmanager::LoadDataMesh()
{
	



	std::filesystem::path dirPath = "./Resources";

	if (!std::filesystem::exists(dirPath) || !std::filesystem::is_directory(dirPath))
	{
		std::cout << "[MeshManager::LoadDataMesh] Error loading mesh! Target directory was either not a path or does not exist!";
		return;
	}

	for (const auto& entry : std::filesystem::directory_iterator(dirPath))
	{
		if (entry.is_regular_file())
		{
			if (entry.path().extension() == ".mesh")
			{
				std::cout << "1000001 Found the following entry!: " << entry.path() << std::endl;
				
				std::ifstream inFile(entry.path(), std::ios::binary);
				
				uint64_t indexCount = 0;
				Serializer::ReadBinaryFileData(inFile, indexCount);

				std::vector<unsigned int > loadedIndecies(indexCount);
				inFile.read(reinterpret_cast<char*>(loadedIndecies.data()), sizeof(unsigned int) * indexCount);


				uint64_t vertexCount = 0;
				Serializer::ReadBinaryFileData(inFile, vertexCount);

				std::vector<Vertex> loadedVertices(vertexCount);
				inFile.read(reinterpret_cast<char*>(loadedVertices.data()), sizeof(Vertex) * vertexCount);



				std::shared_ptr<Mesh> toAdd = std::make_shared<Mesh>(loadedVertices, loadedIndecies, TextureManager::MakeDefaultTextures());
				toAdd->setShader(ShaderManager::MakeShader());

				if (toAdd)
				{
					MeshList.push_back(toAdd);
				}
			}
		}
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

		if (m->GetName() == Serializer::PathToName(m->path))
		{
			return m;
		}
	}
	std::cerr << "Could not find mesh with path: " << tPath << std::endl;
	return nullptr;
}

std::vector<std::shared_ptr<HertzTexture>> Meshmanager::GetDefaultTextures() //depricated
{
	std::vector<std::shared_ptr<HertzTexture>> textures;
	std::shared_ptr<HertzTexture> diffuse  =	std::make_shared<HertzTexture>("./texture./container2.png", true);
	std::shared_ptr<HertzTexture> specular =	std::make_shared<HertzTexture>("./texture/container2_specular.png", true);


	diffuse->m_type = "texture_diffuse";
	specular->m_type = "texture_specular";

	diffuse->m_texturetype = TextureType::Diffuse;
	specular->m_texturetype = TextureType::Specular;

	textures.push_back( diffuse );
	textures.push_back(specular);

	return textures;
}


