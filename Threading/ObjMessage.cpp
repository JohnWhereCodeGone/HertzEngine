#include "ObjMessage.h"





ObjMessage::ObjMessage(const std::string& tPath)
{
	this->m_type = MessageType::LoadOBJ;
	this->m_tPath = tPath;
}

void ObjMessage::QueuePop()
{
	
}


// ---------------------

ObjLoadedMessage::ObjLoadedMessage(std::shared_ptr<ObjData> data, const char* tPath)
{
	this->m_type = MessageType::LoadedResource;
	this->m_data = data;
	this->m_sPath = tPath;

}



void ObjLoadedMessage::SetLoadedMesh(std::shared_ptr<Mesh> meshToAdd)
{
	this->m_loadedMesh = meshToAdd;
}

std::shared_ptr<Mesh> ObjLoadedMessage::GetLoadedMesh()
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

std::shared_ptr<ObjData> ObjLoadedMessage::GetObjData()
{
	return m_data;
}

//Loaded
void ObjLoadedMessage::QueuePop()
{

}
