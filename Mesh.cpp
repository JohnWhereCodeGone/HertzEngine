#include "Mesh.h"
#include "ObjLoader.h"
#include "Objects/VirtualObject.h"
#include <unordered_map>




void Mesh::Attach(VirtualObject& obj)
{
	int error = 0;

	Shader* shad = obj.GetShader();
	Transform* trans = obj.GetTransform();
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

Mesh::Mesh(const ObjData &data, std::vector<HertzTexture*> textures, const char* tPath)
{

	//REMOVE ME
	transform = new Transform();

	indiciesSize = indicies.size();
	this->textures = textures;
	path = tPath;

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

	//pos
	//make sure there's a case for handling lack of texcoords

	//std::cout << std::endl;
	//for (const auto& e : indicies)
	//{
	//	std::cout << e;
	//}
	//std::cout << std::endl;
	//std::cout << "VAO: " << VAO << ", VBO: " << VBO << ", EBO: " << EBO << std::endl;
	//std::cout << "Vertex count: " << verticesold.size() << ", Index count: " << data.indicies.size() << std::endl;
	//if (!verticesold.empty())
	//{
	//	for (size_t i = 0; i < verticesold.size(); ++i)
	//	{
	//		std::cout << verticesold[i].vPos.x << " " << verticesold[i].vPos.y << " " << verticesold[i].vPos.z << " " << verticesold[i].vTexCoords.x << " " << verticesold[i].vTexCoords.y << " " << verticesold[i].vNormal.x << " " << verticesold[i].vNormal.y << " " << verticesold[i].vNormal.z;
	//		if ((i + 1) % 8 == 0) { 
	//			std::cout << std::endl;
	//		}
	//	}
	//}


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
		std::string name = textures[i]->type;

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
		TextureType type = textures[i]->texturetype;
		std::string name = textures[i]->type;

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

void Mesh::SetTextures(std::vector<HertzTexture*> texin)
{
	this->textures = texin;
}
void Mesh::setShader(Shader* nShader)
{
	this->shader = nShader;
}
Shader* Mesh::getShader()
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
	// TODO: insert return statement here




Mesh::Mesh(std::vector<Vertex> verticies, std::vector<unsigned int> indicies, std::vector<HertzTexture*> textures)
{

	

	this->indicies = indicies;
	this->textures = textures;

	//shader = new Shader();

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

