
#version 330 core


in vec2 TexCoord;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 viewPos;

void main()

{
	FragColor = vec4(1, 0, 1, 1);
}