#version 330 core

in vec3 datas;
uniform vec4 appColors;

out vec4 FragColor;

void main()
{
	FragColor = appColors;
}