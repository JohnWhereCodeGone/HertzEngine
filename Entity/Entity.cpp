#include "Entity.h"
#include "../Transform.h"
#include "../Mesh.h"

Entity::Entity() : VirtualObject()
{
	//std::cout << "constructor entity called" << std::endl;
	

}



void Entity::Update(double Deltatime, std::shared_ptr<Camera> cam)
{
	//update model with pos.
	ShaderPtr shad = GetShader();
	TransformPtr trans = GetTransform();
	
	if (shad)
	{

		if (m_isSatellite && cam)
		{
			
			trans->UpdateModelPlanetary(shad, cam);

		}
		else
		{
			trans->UpdateModel(shad);
		}


	}
	MeshPtr mesh = this->GetMesh();

	if (GetDiffuseMap())
	{
		GetDiffuseMap()->m_texturetype = Diffuse;
	}
	if (GetSpecularMap())
	{
		GetSpecularMap()->m_texturetype = Specular;
	}
	if (mesh)
	{
		mesh->Attach(*this);
		mesh->Render();
	}
	



}



		/*
		MeshPtr temp = this->GetMesh();
		if (temp)
		{
			temp->transform = this->GetTransform();
			temp->parent = this;
			temp->setShader(this->GetShader());
			if (!this->GetTextures().empty())
			{
				temp->SetTextures(this->GetTextures());
			}
			
			temp->Render();

		}
		*/


