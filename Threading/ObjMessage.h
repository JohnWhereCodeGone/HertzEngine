#pragma once

#include "Messaging.h"

class Mesh;

class ObjMessage : public Message //loads mesh in new thread
{
public:

	ObjMessage(const std::string &tPath);

	std::string m_tPath;
	void QueuePop() override;

};

class ObjLoadedMessage : public Message //reference to loaded mesh for main thread
{
public:

	ObjLoadedMessage(Mesh* mesh);
	
	void SetLoadedMesh(Mesh* meshToAdd);
	Mesh* GetLoadedMesh();

private:

	Mesh* m_loadedMesh;
	void QueuePop() override;

};