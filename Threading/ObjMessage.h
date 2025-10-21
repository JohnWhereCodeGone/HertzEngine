#pragma once
#include "../ObjLoader.h"
#include "Messaging.h"

class Mesh;

class ObjMessage : public Message // loads mesh in new thread
{
public:

	ObjMessage(const std::string& tPath);

	std::string m_tPath;
	void QueuePop() override;

};

class ObjLoadedMessage : public Message // finished loading/reference to loaded mesh for main thread
{
public:

	ObjLoadedMessage(std::shared_ptr<ObjData> data, const char* tPath = nullptr);
	
	void SetLoadedMesh(std::shared_ptr<Mesh> meshToAdd);
	std::shared_ptr<Mesh> GetLoadedMesh();

	std::shared_ptr<ObjData> GetObjData();

	std::string m_sPath;
	

private:

	std::shared_ptr<ObjData> m_data;
	std::shared_ptr<Mesh> m_loadedMesh;
	void QueuePop() override;

};