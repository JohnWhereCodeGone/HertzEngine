#include "Entity.h"
#include "../Transform.h"


Entity::Entity() : VirtualObject()
{
	

}



void Entity::Update(float Deltatime)
{
	//update model with pos.
	ShaderPtr shad = GetShader();
	TransformPtr trans = GetTransform();
	
	if (shad)
	{
		trans->Move(Deltatime);
		trans->UpdateModel(shad);


	}



}


 