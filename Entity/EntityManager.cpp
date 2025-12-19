#include "EntityManager.h"
#include "../Entity/Entity.h"
#include "../Component.h"
#include "../Mesh.h"
#include "../HertzEngine.h"

unsigned int EntityManager::count = 0;



std::shared_ptr<Entity> EntityManager::CreateEntity()
{
	EntityPtr en = std::make_shared<Entity>();
	en->SetShader(HertzEngine::GetDefaultShader());


	if (en)
	{
		
		std::string title = "Entity ";
		title.append(std::to_string(count));

		en->SetName(title);
		count++;
		m_entityList.push_back(en);
		return en;
	}
	else
	{
		std::cerr << "EntityManager::CreateEntity - Failed to add entity!" << std::endl;
		return nullptr;
	}

}

void EntityManager::DeleteEntity(EntityPtr to_delete)
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
			//this should be the only observer.
			m_entityList.erase(it);

			std::cout << "Entity manager: Removed entity " << name << std::endl;
			//count--;
			return;
		}
	}

	std::cout << "Entity manager: Error! Failed to delete entity." << std::endl;
}

bool EntityManager::AddComponent(Component* to_add, EntityPtr add_to)
{

	
	return true;

}

bool EntityManager::RemoveComponent(Component* to_remove)
{
	return false;
}

void EntityManager::Update(float DeltaTime, std::shared_ptr<Camera> cam)
{
	for (EntityPtr en : m_entityList)
	{

		en->Update(HertzEngine::DeltaTime(), cam);
		//std::cout << en->GetTransform()->GetPos().x << " " << en->GetTransform()->GetPos().y << " " << en->GetTransform()->GetPos().z << std::endl;
	}
}


