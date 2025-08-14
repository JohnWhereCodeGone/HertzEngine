#pragma once
#include <iostream>
#include "vector"

class Entity;
class Component;

class EntityManager
{

public:

	Entity* CreateEntity();
	void DeleteEntity(Entity* to_delete);

	bool  AddComponent(Component* to_add, Entity* add_to);
	bool  RemoveComponent(Component* to_remove);


	std::vector<Entity*> m_entityList;

	void Update();

private:

protected:
	static unsigned int count;

};

