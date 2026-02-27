#include "Trail.h"
#include "ShaderManager.h"





Trail::Trail(std::shared_ptr<Transform> t, std::shared_ptr<Shader> shad)
{
	if (!shad)
	{
		this->m_shad = std::make_unique<Shader>(".\Shaders\fragmentLineShader.glsl");

	}
	else
	{
		this->m_shad = shad;
	}

	this->m_trans = t;

	t->SetPos(glm::vec3(0.0f));
	t->SetScale(glm::vec3(1.0f));
	t->SetScale(glm::vec3(1.0f));


	if (debug)
	{
		this->m_vertices.push_back(glm::vec3(0));
		this->m_vertices.push_back(glm::vec3(1));
	}

	glfwInit();


}

void Trail::glfwInit()
{

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), m_vertices.data(), GL_DYNAMIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);
	

}

void Trail::Update(double dT)
{

	if (debug)
	{
		Draw();
		return;
	}

	constexpr float defaultTime = 0.5f;


	if (m_trans)
	{
		m_Accumulator += dT;

		while (m_Accumulator >= defaultTime)
		{

			if (m_points.size() >= MAX_POINTS)
			{
				m_points.pop_front();
			}

			m_points.push_back(m_trans->GetPos()); //change this to visual pos later

			UpdateBuffer();

			m_Accumulator -= defaultTime;

		}
	}

	Draw();



}



void Trail::UpdateBuffer()
{
	m_vertices.clear();
	m_vertices.reserve(m_points.size());
	for (const auto& point : m_points)
	{
		m_vertices.push_back((glm::vec3)point);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(glm::vec3), m_vertices.data(), GL_DYNAMIC_DRAW);
}

void Trail::Draw()
{

	glLineWidth(1.0f);
	if (!m_shad)
	{
		return;
	}
	m_shad->Use();
	m_trans->UpdateModel(m_shad);
	
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_STRIP, 0, m_vertices.size());
	glBindVertexArray(0);

}

/*
void Transform::UpdateModel(std::shared_ptr<Shader> shader)
{
	if (!shader)
		return;

	glm::mat4 transmat = glm::mat4(1.0f);


	// use quaternions for rotation to avoid 'gimbal lock' - lest you be branded a heretic.
	transmat = glm::translate(transmat, (glm::vec3)m_vPos);
	transmat = glm::rotate(transmat, glm::radians(m_vRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

	transmat = glm::rotate(transmat, glm::radians(m_vRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

	transmat = glm::rotate(transmat, glm::radians(m_vRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transmat = glm::scale(transmat, (glm::vec3)m_vScale);



	shader->Use();
	shader->setMat4("model", transmat);
	this->m_model = transmat;


}

*/


/*
in vec2 TexCoord;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 viewPos;

void main()

{
	FragColor = vec4(1, 0, 1, 1);
}
*/

/*
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec3 ourColour;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;



uniform float xOffset;
uniform mat4 transform;

uniform bool isLight;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{

	if (isLight)
	{
		gl_Position = projection * view * model * vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);
	}
	Normal = mat3(transpose(inverse(model))) * aNormal;
	TexCoord = aTexCoord;
	FragPos = vec3(model * vec4(aPos, 1.0));
	gl_Position = projection * view * vec4(FragPos, 1.0);
}



//model is worldpos

//gl_Position = projection * view * model * vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);

*/