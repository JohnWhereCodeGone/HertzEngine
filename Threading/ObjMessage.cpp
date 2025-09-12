#include "ObjMessage.h"



ObjMessage::ObjMessage(const std::string &tPath)
{
	this->m_type = MessageType::LoadOBJ;
	this->m_tPath = tPath;
}

void ObjMessage::QueuePop()
{
	
}


// ---------------------

ObjLoadedMessage::ObjLoadedMessage(Mesh* mesh)
{
	this->m_type = MessageType::LoadedResource;
	
	if (mesh)
	{
		this->m_loadedMesh = mesh;
	}
	else
	{
		this->m_loadedMesh = nullptr;
		std::cout << "ObjLoadedMessage::Constructor - Mesh was nullptr, I am a danger!" << std::endl;
	}
}

void ObjLoadedMessage::SetLoadedMesh(Mesh* meshToAdd)
{
	this->m_loadedMesh = meshToAdd;
}

Mesh* ObjLoadedMessage::GetLoadedMesh()
{
	if (m_loadedMesh)
	{
		return m_loadedMesh;
	}
	else
	{
		return nullptr;
	}
}

//Loaded
void ObjLoadedMessage::QueuePop()
{

}
