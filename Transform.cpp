#include "Transform.h"


Transform::Transform()
{
	this->vPos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->vRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->vScale = glm::vec3(1.0f, 1.0f, 1.0f);
	this->model = glm::mat4(1.0f);
	this->shader = {};
}

Transform::Transform(glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale, Shader* shader)
{
	this->vPos = pos;
	this->vRotation = rotation;
	this->vScale = scale;
	this->model = glm::mat4(1.f);
	
	if (shader)
	{
		this->shader = shader;
	}
	else
		this->shader = nullptr;
	
}
glm::vec3& Transform::GetPos()
{
	return this->vPos;
}

glm::vec3& Transform::GetScale()
{
	return this->vScale;
}

glm::vec3& Transform::GetRot()
{
	return this->vRotation;
}

// 3 types of light, point point light, dir light, spotlight <- structure this into a class that handles all shaders.
// then mip settings, UI add functions from Transform to update pos, rotation, scale.
void Transform::SetPos(const glm::vec3& newPos)
{
	this->vPos = newPos;
}

void Transform::SetRot(const glm::vec3& newRot)
{
	this->vRotation = newRot;
}

void Transform::SetScale(const glm::vec3& newScale)
{
	this->vScale = newScale;
}

void Transform::UpdateModel(Shader* shader)
{
	if (!shader)
		return;
	auto model = glm::mat4(1.0f);


	if (shader)
	{
		model = glm::translate(model, vPos);
		model = glm::rotate(model, glm::radians(vRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(vRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(vRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, vScale);

		shader->Use();
		shader->setMat4("model", model);

	}
	else
	{
		std::cerr << "Transform: Error! Shader was nullptr" << std::endl;
	}



}
