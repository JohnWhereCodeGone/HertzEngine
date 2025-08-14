#include "Entity.h"
#include "../Transform.h"

Entity::Entity() : VirtualObject()
{
	

}



void Entity::Update()
{
	//update model with pos.
	Shader* shad = GetShader();
	Transform* trans = GetTransform();

	if (shad)
	{
		trans->UpdateModel(shad);

	}



}
