#include "Mesh.h"
#include "ObjLoader.h"
#include "Objects/VirtualObject.h"
#include <unordered_map>
#include "ShaderManager.h"
#include "TextureManager.h"




void Mesh::Attach(VirtualObject& obj)
{
	int error = 0;

	ShaderPtr shad = obj.GetShader();
	std::shared_ptr<Transform> trans = obj.GetTransform();
	textures = obj.GetTextures();

	if (shad && trans)
	{
		this->shader = shad;
		this->transform = trans;
	}
	else
	{
		std::cerr << "Mesh: error at " + this->path << " shader/transform was null when trying to attach." << std::endl;
		return;
	}


}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

Mesh::Mesh(const ObjData &data, std::vector<std::shared_ptr<HertzTexture>> textures, const char* tPath)
{

	//REMOVE ME
	transform = std::make_shared<Transform>();

	indiciesSize = indicies.size();
	this->textures = textures;
	if (tPath)
	{

		path = tPath;
	}

	// The data is almsot right, but the faces reference the wrong vt, vn and vpos due to indice issue!!!


	std::vector<glm::vec3> vPositions = data.vPos;
	std::unordered_map<VertexKey, unsigned int, VertexKeyHash> meshmap;


	for (size_t i = 0; i < data.vPosIndices.size(); ++i)
	{

		int posIndex = data.vPosIndices[i];
		int uVIndex = (i < data.vTexCoordIndices.size()) ? data.vTexCoordIndices[i] : -1;
		int normIndex = (i < data.vNormalIndices.size()) ? data.vNormalIndices[i] : -1;

		VertexKey key{ posIndex, uVIndex, normIndex };

		if (meshmap.count(key) == 0)
		{
			Vertex vert;
			vert.vPos = data.vPos[posIndex];

			if (uVIndex != -1 && uVIndex < data.vTexCoordIndices.size() && !data.vTexCoords.empty())
			{
				vert.vTexCoords = data.vTexCoords[uVIndex];

				//vert.vTexCoords.y = 1.0f - vert.vTexCoords.y;
			}
			if (normIndex != -1 && normIndex < data.vNormalIndices.size())
			{
				vert.vNormal = data.vNormal[normIndex];
			}
			vertices.push_back(vert);
			meshmap[key] = static_cast<unsigned int>(vertices.size() - 1); // keep -1.
		}
		indicies.push_back(meshmap[key]);
	}



	InitMesh();


	if (glIsVertexArray(VAO) == GL_FALSE)
	{
		std::cout << "Mesh: VAO Creation Failure" << std::endl;
	}

	


	indiciesSize = indicies.size();
}


// layout(location = 0) in vec3 aPos; 
// layout(location = 1) in vec2 aTexCoord;
// layout(location = 2) in vec3 aNormal;


//Meshes can't use different textures at this point. Fix

// Cache shader, texture, mesh in a virtual class. Update pointers rather than add new data. 

void Mesh::Draw(Shader& shader)
{
	
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {}

	shader.Use();

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "MESH - ActiveTexture Error: " << error << std::endl;
		}

		std::string number;
		std::string name = textures[i]->m_type;

		if (name == "texture_diffuse")
		{
			number = std::to_string(i + 1);
		}
		else if (name == "texture_specular")
		{
			number = std::to_string(i + 1);
		}
		else if (name == "texture_normal")
		{
			number = std::to_string(i + 1);
		}

		shader.setInt(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i]->GetTexture());

		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "MESH - Texture Bind Error: " << error << std::endl;
		}
	}

	//clear error
	while ((error = glGetError()) != GL_NO_ERROR) {}

	//draw
	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, (void*)0);


	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
}

void Mesh::Render()
{
	if (!shader)
	{
		std::cout << "Shader is still nullptr!" << std::endl;
	}
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {}

	shader->Use();

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "MESH - ActiveTexture Error: " << error << std::endl;
		}

		std::string number;
		TextureType type = textures[i]->m_texturetype;
		std::string name = textures[i]->m_type;

		/*
		switch (type)
		{
		case TextureType::Diffuse :
			number = std::to_string(i + 1);
			break;

		case TextureType::Specular :
			number = std::to_string(i + 1);
			break;

		case TextureType::Normal :
			number = std::to_string(i + 1);
			break;
		}
		*/

		if (name == "texture_diffuse")
		{
			number = std::to_string(i + 1);
		}
		else if (name == "texture_specular")
		{
			number = std::to_string(i + 1);
		}
		else if (name == "texture_normal")
		{
			number = std::to_string(i + 1);
		}

		shader->setInt(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i]->GetTexture());

		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "MESH - Texture Bind Error: " << error << std::endl;
		}
	}

	//clear error
	while ((error = glGetError()) != GL_NO_ERROR) {}

	//draw
	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, (void*)0);


	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(0);
}

void Mesh::SetTextures(std::vector<std::shared_ptr<HertzTexture>> texin)
{
	this->textures = texin;
}
void Mesh::setShader(ShaderPtr nShader)
{
	this->shader = nShader;
}
std::shared_ptr<Shader> Mesh::getShader()
{
	if (shader)
	{
		return shader;
	}
	else
	{
		return nullptr;
	}
}
std::string& Mesh::GetName()
{
	return this->m_NameM;
	// TODO: insert return statement here
}
void Mesh::SetName(const std::string& newName)
{
	this->m_NameM = newName;
}
	// TODO: insert return statement here




Mesh::Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies, std::vector<std::shared_ptr<HertzTexture>> textures)
{
	//used for loading from .mesh file
	

	this->indicies = indicies;
	this->vertices = verticies;
	
	this->shader = ShaderManager::MakeShader();
	transform = std::make_shared<Transform>();
	this->indiciesSize = sizeof(indicies);
	this->textures = textures;

	InitMesh();
}
//void Mesh::Draw()
//{
//	if (shader == nullptr)
//	{
//		shader = new Shader();
//	}
//	shader->Use();
//	int diffuseNr = 1;
//	int specularNr = 1;
//	int normalNr = 1;
//
//	for (unsigned int i = 0; i < textures.size(); i++)
//	{
//		glActiveTexture(GL_TEXTURE0 + i);
//
//		std::string number;
//		std::string name = textures[i]->type;
//
//		if (name == "texture_diffuse")
//		{
//			number = std::to_string(diffuseNr++);
//		}
//		else if (name == "texture_specular")
//		{
//			number = std::to_string(specularNr++);
//		}
//		else if (name == "texture_normal")
//		{
//			number = std::to_string(normalNr++);
//		}
//
//		shader->setInt(("material." + name + number).c_str(), i);
//		glBindTexture(GL_TEXTURE_2D, textures[i]->GetTexture());
//
//
//	}
//	glActiveTexture(GL_TEXTURE0);
//
//	glBindVertexArray(VAO);
//	glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//}




void Mesh::InitMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), &indicies[0], GL_STATIC_DRAW);
	

	//pos
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	//texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, vTexCoords));
	glEnableVertexAttribArray(1);
	//norm
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, vNormal));
	glEnableVertexAttribArray(2);


	//Indicies steps wrongly, most likely wrong order

	//add remove entities, adjust name position

	glBindVertexArray(0);
}

