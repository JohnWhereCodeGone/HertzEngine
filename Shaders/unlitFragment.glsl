#version 330 core
in vec2 TexCoord;

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float transition;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform bool isLight;
uniform vec3 lightPos;

uniform vec3 viewPos;

struct Material
{
    sampler2D diffuse1;
    sampler2D diffuse2;
    sampler2D diffuse3;
    
    sampler2D specular1;
    sampler2D specular2;
    sampler2D specular3;

    sampler2D normal1;
    sampler2D normal2;
    sampler2D normal3;
    float shine;
};





uniform Material material;
uniform bool isSun;

void main()
{

		vec3 debugtex = vec3(texture(material.diffuse1, TexCoord));
		FragColor = vec4(debugtex, 1.0);
    

    
}