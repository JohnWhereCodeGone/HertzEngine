#include "EntityManager.h"
#include "../Entity/Entity.h"
#include "../Component.h"
#include "../Mesh.h"
#include "../HertzEngine.h"

unsigned int EntityManager::count = 0;

Entity* EntityManager::CreateEntity()
{
	Entity* en = new Entity;
	en->SetShader(HertzEngine::GetDefaultShader());


	if (en)
	{
		m_entityList.push_back(en);
		return en;
	}
	else
	{
		std::cerr << "Failed to add entity!" << std::endl;
		return nullptr;
	}

}

void EntityManager::DeleteEntity(Entity* to_delete)
{
	if (!to_delete)
	{
		std::cout << "Entity manager: Error! to_delete was nullptr." << std::endl;
		return;
	}
	auto end = m_entityList.end();
	std::string name = *to_delete->GetName();

	for (auto it = m_entityList.begin(); it != end; it++)
	{
		if (*it == to_delete)
		{
			delete* it;
			m_entityList.erase(it);

			std::cout << "Entity manager: Removed entity " << name << std::endl;
			count--;
			return;
		}
	}

	std::cout << "Entity manager: Error! Failed to delete entity." << std::endl;
}

bool EntityManager::AddComponent(Component* to_add, Entity* add_to)
{

	
	if (to_add && add_to)
	{
		Mesh* temp = dynamic_cast<Mesh*>(to_add);
		temp->Attach(*add_to);
		return true;
	}
	else
	{
		std::cerr << "Entity manager: Error! Adding component failed" << std::endl;
	}

}

bool EntityManager::RemoveComponent(Component* to_remove)
{
	return false;
}

void EntityManager::Update()
{
	for (Entity* em : m_entityList)
	{
		em->Update();
	}

}
