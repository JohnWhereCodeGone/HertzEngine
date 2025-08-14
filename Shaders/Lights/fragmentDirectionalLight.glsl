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



struct Lightdirectional {

    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

struct Light {

    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

};

uniform Light light;
uniform Lightdirectional;


void main()
{
    FragColor = vec4(1.0);
    
} 