#version 330 core

in vec3 datas;

out vec4 FragColor;

void main()
{
	FragColor = vec4(datas.x, datas.y, datas.z, 1.0);
}