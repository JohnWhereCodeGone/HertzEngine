
#version 330 core


in vec2 TexCoord;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 trailColor;

void main()

{
	FragColor = vec4(trailColor, 1);
}