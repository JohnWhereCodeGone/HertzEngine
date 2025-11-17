#pragma once
#include <iostream>
#include "vector"

class Entity;
class Component;

class EntityManager
{
	using EntityPtr = std::shared_ptr<Entity>;

public:
	
	EntityPtr CreateEntity();
	void DeleteEntity(EntityPtr to_delete);

	bool  AddComponent(Component* to_add, EntityPtr add_to);
	bool  RemoveComponent(Component* to_remove);


	std::vector<std::shared_ptr<Entity>> m_entityList;

	void Update(float DeltaTime);

private:

	

protected:
	static unsigned int count;

};

